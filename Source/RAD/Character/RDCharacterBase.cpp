// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RDCharacterBase.h"

// Sets default values
ARDCharacterBase::ARDCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARDCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARDCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

