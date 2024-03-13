// Copyright Epic Games, Inc. All Rights Reserved.


#include "CafeGameModeBase.h"

#include "CafeCharacter.h"
#include "CafePlayerController.h"
#include "Kismet/GameplayStatics.h"

/* Sets default values */
ACafeGameModeBase::ACafeGameModeBase()
{
	/* Find & assign the default pawn class from blueprint */
	static ConstructorHelpers::FClassFinder<ACafeCharacter> DefaultPawn(TEXT("/Game/Cafe/Blueprints/BP_Barista"));
	if (DefaultPawn.Succeeded())
	{
		DefaultPawnClass = DefaultPawn.Class;
	}
	/* Set the default player controller class */
	PlayerControllerClass = ACafePlayerController::StaticClass();
}

/* Updates the player's camera when they spawn */
APlayerController* ACafeGameModeBase::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PlayerController = Super::SpawnPlayerController(InRemoteRole, Options);

	if (ACafePlayerController* CafePlayerController = Cast<ACafePlayerController>(PlayerController))
	{
		/* Assign camera manager to the first instance found */
		if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACafeCameraManager::StaticClass()))
		{
			CameraManager = Cast<ACafeCameraManager>(FoundActor);

			/* Set player's camera to default */
			ACafeCamera* DefaultCamera = CameraManager->GetCamera(ECameraView::Default);
			CafePlayerController->SetCafeCamera(DefaultCamera);
		}
	}
	
	return PlayerController;
}
