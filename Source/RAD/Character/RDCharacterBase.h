// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "RDCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
enum class EAbilityID : uint8;
class UAbilitySystemComponent;
class URDAttributeSet;
class URDAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class RAD_API ARDCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARDCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "RD | Camera")
	UCameraComponent* TopDownCameraComponent;


	FORCEINLINE USpringArmComponent* GetCameraBoom() { return CameraBoom; }

private:
	UPROPERTY(EditAnywhere, Category = "RD | Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;


	// GAS
public:
	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	TWeakObjectPtr<URDAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	TWeakObjectPtr<URDAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable, Category = "RD | GAS")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "RD | GAS")
	float GetMaxHealth() const;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	FText CharacterName;

	UPROPERTY(EditAnywhere, Category = "RD | GAS")
	UAnimMontage* DeathMontage;

	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
