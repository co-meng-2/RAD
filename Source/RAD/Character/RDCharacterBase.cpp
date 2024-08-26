// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

