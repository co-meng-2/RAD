// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GameplayEffectTypes.h" // FOnAttributeChangeData
#include "RDPlayerState.generated.h"

class URDAbilitySystemComponent;
class URDAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class RAD_API ARDPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARDPlayerState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "RD | GAS")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "RD | GAS")
	float GetMaxHealth() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "RD | GAS")
	URDAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category = "RD | GAS")
	URDAttributeSet* AttributeSet;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

public:
	URDAttributeSet* GetAttributeSet();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
