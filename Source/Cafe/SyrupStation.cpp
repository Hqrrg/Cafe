// Fill out your copyright notice in the Description page of Project Settings.


#include "SyrupStation.h"
#include "BaristaCharacter.h"

// Sets default values
ASyrupStation::ASyrupStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASyrupStation::SetInteractedPawn_Implementation(APawn* Pawn)
{

	Super::SetInteractedPawn_Implementation(Pawn);

	FInventory* BaristaInventory = &BaristaRef->GetInventory();

	IngredientArray.Add(EIngredient::CaramelSyrup);
	IngredientArray.Add(EIngredient::HazelnutSyrup);
	IngredientArray.Add(EIngredient::GingerbreadSyrup);
}

