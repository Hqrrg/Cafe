// Copyright Epic Games, Inc. All Rights Reserved.


#include "CafeGameModeBase.h"

#include "CafeCharacter.h"
#include "BaristaPlayerController.h"
#include "CustomerCharacter.h"
#include "CustomerPlayerStart.h"
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
	PlayerControllerClass = ABaristaPlayerController::StaticClass();
}

void ACafeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	/* Assign queue manager to the first instance found */
	if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACafeQueueManager::StaticClass()))
	{
		QueueManager = Cast<ACafeQueueManager>(FoundActor);	
	}

	if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerPlayerStart::StaticClass()))
	{
		FTransform SpawnTransform = FoundActor->GetTransform();
		FActorSpawnParameters SpawnParams;
		ACustomerCharacter* SpawnedCustomer = GetWorld()->SpawnActor<ACustomerCharacter>(ACustomerCharacter::StaticClass(), SpawnTransform, SpawnParams);
		SpawnedCustomer->Setup(FString("Dave"));
		SpawnedCustomer->SetActorRotation(FRotator(0.0f, -25.0f, 0.0f));

		ACustomerCharacter* SpawnedCustomer1 = GetWorld()->SpawnActor<ACustomerCharacter>(ACustomerCharacter::StaticClass(), SpawnTransform, SpawnParams);
		SpawnedCustomer1->Setup(FString("Dave"));
		SpawnedCustomer1->SetActorRotation(FRotator(0.0f, -25.0f, 0.0f));

		ACustomerCharacter* SpawnedCustomer2 = GetWorld()->SpawnActor<ACustomerCharacter>(ACustomerCharacter::StaticClass(), SpawnTransform, SpawnParams);
		SpawnedCustomer2->Setup(FString("Dave"));
		SpawnedCustomer2->SetActorRotation(FRotator(0.0f, -25.0f, 0.0f));
	}
}

/* Updates the player's camera when they spawn */
APlayerController* ACafeGameModeBase::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* PlayerController = Super::SpawnPlayerController(InRemoteRole, Options);

	if (ABaristaPlayerController* CafePlayerController = Cast<ABaristaPlayerController>(PlayerController))
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

/* Return nullptr to stop gamemode from spawning an extra player pawn */
UClass* ACafeGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return nullptr;
}
