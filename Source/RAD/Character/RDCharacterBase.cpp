// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RAD/GAS/RDAttributeSet.h"
#include "GAS/RDAbilitySystemComponent.h"

// Sets default values
ARDCharacterBase::ARDCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// GetCapsuleComponent();
	// 카메라 회전 영향 X.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	// FRotator는 pitch, yaw, roll 순서
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	// 평면에서의 이동만 허용
	GetCharacterMovement()->bConstrainToPlane = true;
	// 시작할 때, 평면에 snap.
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// 부모 영향 안 받는 회전
	CameraBoom->SetUsingAbsoluteRotation(true);
	// 카메라 부딪히면 줌X.
	CameraBoom->bDoCollisionTest= false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// Camera를 SpringArm끝에 붙여줌.
	TopDownCameraComponent->SetupAttachment(CameraBoom /*,USpringArmComponent::SocketName*/);

	// 바꿀 수 없음 -> Tick할지 등록
	PrimaryActorTick.bCanEverTick = true;

	// 바꿀 수 있음 -> Tick 언제부터 시작할지 결정
	PrimaryActorTick.bStartWithTickEnabled = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));

	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ARDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ARDCharacterBase::IsAlive() const
{
	return GetHealth() > 0.f;
}

int32 ARDCharacterBase::GetAbilityLevel(EAbilityID AbilityID)
{
	return 1;
}



void ARDCharacterBase::Die()
{
}

void ARDCharacterBase::FinishDying()
{
}

float ARDCharacterBase::GetHealth() const
{
	return AttributeSet.Get()->GetHealth();
}

float ARDCharacterBase::GetMaxHealth() const
{
	return AttributeSet.Get()->GetMaxHealth();
}

void ARDCharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilityGiven)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			 FGameplayAbilitySpec(StartupAbility));
	}

	AbilitySystemComponent->bCharacterAbilityGiven = true;
}

void ARDCharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bStartupEffectApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for(TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		// @todo : Effect나 Ability나 Level을 넣어줄 수 있는 구조 만들기
		FGameplayEffectSpecHandle  NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if(NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->bStartupEffectApplied = true;
}

void ARDCharacterBase::InitializeAttributes()
{
	if (!AttributeSet.IsValid() || !DefaultAttributes)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	// 인스턴스를 만든 오브젝트 설정
	EffectContext.AddSourceObject(this);

	// Spec을 생성하고 SpecHandle을 반환.
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void ARDCharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilityGiven)
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for(const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for(auto& ToRemove : AbilitiesToRemove)
	{
		AbilitySystemComponent->ClearAbility(ToRemove);
	}

	AbilitySystemComponent->bCharacterAbilityGiven = false;
}

void ARDCharacterBase::SetHealth(float Health)
{
	AttributeSet->SetHealth(Health);
}

UAbilitySystemComponent* ARDCharacterBase::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent.Get());
}


