// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractablePawn.h"


// Sets default values
AInteractablePawn::AInteractablePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractablePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractablePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AInteractablePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/* Interact behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
void AInteractablePawn::Interact_Implementation()
{
	IInteractable::Interact_Implementation();
}

/* Selection behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
void AInteractablePawn::Selected_Implementation(bool Is)
{
	IInteractable::Selected_Implementation(Is);
}

