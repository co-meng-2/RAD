// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "GAS/RDAbilitySystemComponent.h"
#include "GAS/RDAttributeSet.h"
#include "Player/RDPlayerState.h"

ARDPlayerCharacter::ARDPlayerCharacter()
{
}

void ARDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARDPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(auto PS = GetPlayerState<ARDPlayerState>())
	{
		AbilitySystemComponent = Cast<URDAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		AttributeSet = PS->GetAttributeSet();
		InitializeAttributes();
		AddStartupEffects();
		AddCharacterAbilities();
	}
}

void ARDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for (int i = (int)EPlayerAbilityID::Ability_1_Q; i <= (int)EPlayerAbilityID::Ability_6_D; ++i)
		{
			if (InputAbilityActions[i])
			{																	 // 실행할 주체 instance
				EI->BindAction<>(InputAbilityActions[i], ETriggerEvent::Triggered, this, &ThisClass::ActivateAbilities, i);
			}
		}

		EI->BindAction(InputDash, ETriggerEvent::Triggered, this, &ThisClass::ActivateDash);
	}
}

void ARDPlayerCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->bCharacterAbilityGiven)
	{
		return;
	}

	for (int idx = 1; idx <= Abilities.Num(); ++idx)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(Abilities[idx], 0, idx, this));
														// InSourceObject -> 능력이 누구로부터 부여되었는지 설정.
	}

	AbilitySystemComponent->bCharacterAbilityGiven = true;
}

void ARDPlayerCharacter::ActivateAbilities(int idx)
{
	if(auto Spec = AbilitySystemComponent->FindAbilitySpecFromInputID(idx))
	{
		auto Handle = Spec->Handle;
		AbilitySystemComponent->TryActivateAbility(Handle);
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Emerald, FString::Printf(TEXT("%i Ability Activated!"), idx));
	}
}

void ARDPlayerCharacter::ActivateDash()
{
	if(auto Spec = AbilitySystemComponent->FindAbilitySpecFromInputID((int)EPlayerAbilityID::Ability_0_Space))
	{
		auto Handle = Spec->Handle;
		AbilitySystemComponent->TryActivateAbility(Handle);
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Emerald, FString::Printf(TEXT("0 Ability Activated!")));
	}
}
