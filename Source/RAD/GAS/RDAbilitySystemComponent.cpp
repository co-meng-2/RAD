// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/RDAbilitySystemComponent.h"

void URDAbilitySystemComponent::ReceivedDamage(URDAbilitySystemComponent* SourceASC, float UnmitigatedDamage,
	float MitigatedDamage)
{
	ReceivedDamageDelegate.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
