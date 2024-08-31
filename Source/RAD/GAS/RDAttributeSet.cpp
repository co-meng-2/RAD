// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/RDAttributeSet.h"

#include "Net/UnrealNetwork.h"

void URDAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URDAttributeSet, Health, OldHealth);
}

void URDAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URDAttributeSet, MaxHealth, OldMaxHealth);
}

void URDAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URDAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URDAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}
