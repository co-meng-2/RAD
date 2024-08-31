// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RDPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Test/RDTestObject.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ARDPlayerController::ARDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::Zero();
}

void ARDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ARDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ARDPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ARDPlayerController::OnSetDestinationTriggered);
		// EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ARDPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ARDPlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to find an Enhanced Input Component!"));
	}
}

void ARDPlayerController::OnInputStarted()
{
	// 제어하는 것의 움직임을 멈춤.
	// StopMovement();
}

bool ARDPlayerController::GetHitResult()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	// bTraceComplex -> 실제 3D모델을 사용해서 trace할지 물체에 적용된 충돌체를 사용하여 할지.
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if(bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	return bHitSuccessful;
}

void ARDPlayerController::OnSetDestinationTriggered()
{
	if (!GetHitResult()) return;

	if (!isFollowingCursor)
		StopMovement();

	isFollowingCursor = true;

	APawn* ControlledPawn = GetPawn();
	if(ControlledPawn)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		// bForce -> ??
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ARDPlayerController::OnSetDestinationReleased()
{
	if (!GetHitResult()) return;

	isFollowingCursor = false;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination/*,FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true*/);
	UE_LOG(LogTemplateCharacter, Warning, TEXT("Character Nav Moving"));
}
