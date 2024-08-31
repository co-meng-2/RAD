// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RDCharacterBase.h"
#include "RDPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RAD_API ARDPlayerCharacter : public ARDCharacterBase
{
	GENERATED_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;
};
