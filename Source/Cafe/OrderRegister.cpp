// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderRegister.h"

#include "BaristaCharacter.h"
#include "CustomerCharacter.h"

// Sets default values
AOrderRegister::AOrderRegister()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AOrderRegister::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	if (BaristaRef->GetCurrentOrder()->IsFulfilled())
	{
		BaristaRef->GetCurrentCustomerRef()->ConcludeOrder();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString("Order not complete"));
	}
}

void AOrderRegister::SetInteractedPawn_Implementation(APawn* Pawn)
{
	IInteractable::SetInteractedPawn_Implementation(Pawn);

	BaristaRef = Cast<ABaristaCharacter>(Pawn);
}
