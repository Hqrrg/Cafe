// Fill out your copyright notice in the Description page of Project Settings.


#include "CoffeeStation.h"

#include "BaristaCharacter.h"

// Sets default values
ACoffeeStation::ACoffeeStation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ACoffeeStation::SetInteractedPawn_Implementation(APawn* Pawn) {

	Super::SetInteractedPawn_Implementation(Pawn);

	IngredientArray.Add(EIngredient::Water);
	IngredientArray.Add(EIngredient::CoffeeBeans);
}