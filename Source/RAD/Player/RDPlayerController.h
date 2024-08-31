// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameFramework/PlayerController.h"
#include "RDPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Warning, All);

UCLASS()
class RAD_API ARDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARDPlayerController();

	UPROPERTY(EditAnywhere, Category="Input")
	float ShortPressThreshold;

	UPROPERTY(EditAnywhere, Category = "Input")
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SetDestinationClickAction;

protected:
	bool bMoveToMouseCursor : true;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

	void OnInputStarted();
	
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

	bool isFollowingCursor;

private:
	bool GetHitResult();
	FVector CachedDestination;
};
