// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RDPlayerState.h"

#include "GAS/RDAbilitySystemComponent.h"
#include "GAS/RDAttributeSet.h"

ARDPlayerState::ARDPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URDAbilitySystemComponent>(FName("AbilitySystempComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// GameplayEffects는 Owning Client에게만 복제
	// GameplayTag와 GameplayQue는 모두에게 복제
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URDAttributeSet>(FName("AttributeBase"));
}

void ARDPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(
			FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),
			EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::StunTagChanged);
	}
}

UAbilitySystemComponent* ARDPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


float ARDPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ARDPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

URDAttributeSet* ARDPlayerState::GetAttributeSet()
{
	return AttributeSet;
}

void ARDPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Emerald, FString::Printf(TEXT("HealthChanged! old : %f new : %f"), Data.OldValue, Data.NewValue));
}

void ARDPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ARDPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
}
