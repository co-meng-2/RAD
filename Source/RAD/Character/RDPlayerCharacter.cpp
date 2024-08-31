// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDPlayerCharacter.h"

#include "GAS/RDAbilitySystemComponent.h"
#include "GAS/RDAttributeSet.h"
#include "Player/RDPlayerState.h"

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
