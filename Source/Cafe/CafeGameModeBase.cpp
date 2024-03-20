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

	/* Find the first instance of customer player start */
	if (AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerPlayerStart::StaticClass()))
	{
		ACustomerPlayerStart* CustomerPlayerStart = Cast<ACustomerPlayerStart>(FoundActor);
		
		FTransform SpawnTransform = CustomerPlayerStart->GetTransform();
		EDirection SpawnDirection = CustomerPlayerStart->GetSpawnDirection();

		/* Initialise a timer that calls "SpawnCustomer" with the spawn transform and spawn direction properties of the customer player start*/
		FTimerDelegate SpawnCustomerTimerDelegate;
		SpawnCustomerTimerDelegate.BindUFunction(this, FName("SpawnCustomer"), SpawnTransform, SpawnDirection);

		GetWorldTimerManager().SetTimer(SpawnCustomerTimerHandle, SpawnCustomerTimerDelegate, 5.0f, true);
	}

	BeginDay(5 * 60);
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

void ACafeGameModeBase::BeginDay_Implementation(float LengthSeconds)
{
}

void ACafeGameModeBase::EndDay_Implementation()
{
}


/* Spawn a customer character */
void ACafeGameModeBase::SpawnCustomer(FTransform SpawnTransform, EDirection SpawnDirection)
{
	/* If there is no room in the queue, return */
	if (CustomerArray.Num() >= GetQueueManager()->GetQueuePoints().Num()) return;
	
	ACustomerCharacter* Customer = nullptr;

	TArray<FString> CustomerRarityAdjustedArray;

	/* Loop through entries in default customer map */
	for (const TPair<FString, ECustomerRarity> Element : DefaultCustomerMap)
	{
		const ECustomerRarity CustomerRarity = Element.Value;
		const FString CustomerName = Element.Key;

		/* Add the customer's name X amount of times to the temporary array. X = ECustomerRarity value */
		for (int i = 0; i < CustomerRarity+1; i++)
		{
			CustomerRarityAdjustedArray.Push(CustomerName);
		}
	}

	/* Ensure array size is bigger than 0 */
	if (CustomerRarityAdjustedArray.IsEmpty()) return;
	
	/* Get a random number between 0 (first index) and the last index of the temporary array */
	int32 Index = FMath::RandRange(0, CustomerRarityAdjustedArray.Num()-1);
	/* Get the customer's name from the array using the index */
	FString CustomerName = CustomerRarityAdjustedArray[Index];

	/* Spawn ACustomerCharacter */
	FActorSpawnParameters SpawnParams;
	Customer = GetWorld()->SpawnActor<ACustomerCharacter>(ACustomerCharacter::StaticClass(), SpawnTransform, SpawnParams);

	/* Setup customer properties */
	Customer->Setup(CustomerName);
	Customer->SetActorRotation(FRotator(0.0f, -25.0f, 0.0f));
	Customer->SetDirection(SpawnDirection);

	/* Add spawned customer to CustomerArray */
	CustomerArray.Push(Customer);
}

void ACafeGameModeBase::RemoveCustomer(ACustomerCharacter* Customer)
{
	CustomerArray.Remove(Customer);
}
