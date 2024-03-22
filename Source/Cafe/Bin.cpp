// Fill out your copyright notice in the Description page of Project Settings.


#include "Bin.h"

#include "BaristaCharacter.h"

// Sets default values
ABin::ABin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABin::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (UOrder* CurrentOrder = BaristaRef->GetCurrentOrder())
	{
		CurrentOrder->ClearTicket();
	}
}

void ABin::SetInteractedPawn_Implementation(APawn* Pawn)
{
	IInteractable::SetInteractedPawn_Implementation(Pawn);

	BaristaRef = Cast<ABaristaCharacter>(Pawn);
}

bool ABin::ShouldBeNextTo_Implementation()
{
	return true;
}

