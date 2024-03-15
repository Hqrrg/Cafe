// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"


// Sets default values
ACustomerCharacter::ACustomerCharacter()
{
	/* Disable tick for this actor to improve performance */
	PrimaryActorTick.bCanEverTick = false;

	/* Pre-initialise default characteristics array with Normal & assign to characteristic property */
	DefaultCharacteristicsArray.Init(ECustomerCharacteristic::Normal, 2);
	Characteristic |= DefaultCharacteristicsArray[0];
	Characteristic |= DefaultCharacteristicsArray[1];
}

// Called when the game starts or when spawned
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Loop through default characteristics array and apply to property */
	for (ECustomerCharacteristic DefaultCharacteristic : DefaultCharacteristicsArray)
	{
		Characteristic |= DefaultCharacteristic;
	}
}

