// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RDAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, URDAbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

UCLASS()
class RAD_API URDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	// 초기화 bool
	bool bCharacterAbilityGiven = false;
	bool bStartupEffectApplied = false;

	FReceivedDamageDelegate ReceivedDamageDelegate;

	virtual void ReceivedDamage(URDAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
