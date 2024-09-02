// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RDCharacterBase.h"
#include "RDPlayerCharacter.generated.h"

class UInputAction;

UENUM()
enum class EPlayerAbilityID : uint16
{
	Ability_0_Space UMETA(DisplayName = "Dash 0 Space"),
	Ability_1_Q UMETA(DisplayName = "Ability 1 Q"),
	Ability_2_W UMETA(DisplayName = "Ability 2 W"),
	Ability_3_E UMETA(DisplayName = "Ability 3 E"),
	Ability_4_A UMETA(DisplayName = "Ability 4 A"),
	Ability_5_S UMETA(DisplayName = "Ability 5 S"),
	Ability_6_D UMETA(DisplayName = "Ability 6 D"),
};

UCLASS()
class RAD_API ARDPlayerCharacter : public ARDCharacterBase
{
	GENERATED_BODY()

public:
	ARDPlayerCharacter();

public:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void AddCharacterAbilities() override;

	UPROPERTY(EditAnywhere, Category="RD | Input")
	TArray<UInputAction*> InputAbilityActions;

	UPROPERTY(EditAnywhere, Category = "RD | Input")
	UInputAction* InputDash;

	void ActivateAbilities(int idx);
	void ActivateDash();
};
