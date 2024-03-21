// Fill out your copyright notice in the Description page of Project Settings.


#include "MilkStation.h"

#include "BaristaCharacter.h"

// Sets default values
AMilkStation::AMilkStation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AMilkStation::SetInteractedPawn_Implementation(APawn* Pawn)
{

	Super::SetInteractedPawn_Implementation(Pawn);

	IngredientArray.Add(EIngredient::Milk);
	IngredientArray.Add(EIngredient::SoyMilk);
	IngredientArray.Add(EIngredient::AlmondMilk);
}
