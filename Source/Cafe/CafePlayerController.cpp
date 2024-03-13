// Fill out your copyright notice in the Description page of Project Settings.


#include "CafePlayerController.h"

#include "CafeCamera.h"

/* Sets the view target to the cafe camera actor */
void ACafePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (CafeCamera) SetViewTarget(CafeCamera);
}

/* Sets the player's camera */
void ACafePlayerController::SetCafeCamera(ACafeCamera* Camera)
{
	CafeCamera = Camera;
	CafeCamera->SetOwningPlayer(this);

	/* Update view target if already possessing pawn */
	if (GetPawn()) SetViewTarget(CafeCamera);
}
