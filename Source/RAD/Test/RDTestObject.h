// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RDTestObject.generated.h"

/**
 * 
 */
UCLASS()
class RAD_API URDTestObject : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	int32 MyIntValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	FString MyStringValue;

    URDTestObject();
};
