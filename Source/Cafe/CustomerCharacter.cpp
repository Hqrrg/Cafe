// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"

#include "CustomerAIController.h"


/* Sets default values for this actors properties */
ACustomerCharacter::ACustomerCharacter()
{
	/* Enable tick for this actor */
	PrimaryActorTick.bCanEverTick = true;

	/* Set AI controller settings */
	AIControllerClass = ACustomerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	/* Find and assign customer character info data table */
	static ConstructorHelpers::FObjectFinder<UDataTable> CustomerCharacterInfoDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_CustomerCharacterInfo.DT_CustomerCharacterInfo"));
	if (CustomerCharacterInfoDataTableAsset.Succeeded())
	{
		CustomerCharacterInfoDataTable = CustomerCharacterInfoDataTableAsset.Object;
	}

	/* Find and assign customer modifier info data table */
	static ConstructorHelpers::FObjectFinder<UDataTable> CustomerModifierInfoDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_CustomerModifierInfo.DT_CustomerModifierInfo"));
	if (CustomerModifierInfoDataTableAsset.Succeeded())
	{
		CustomerModifierInfoDataTable = CustomerModifierInfoDataTableAsset.Object;
	}
}

/* Called when this actor is spawned */
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateFlipbook();
}

/* Called every frame */
void ACustomerCharacter::Tick(float DeltaSeconds)
{
	/* If the customer is moving */
	if (IsMoving())
	{
		/* Get player velocity in relation to the player */
		FRotator Rotation = GetActorRotation();
		FVector Velocity = GetVelocity();
		FVector RelativeVelocity = Rotation.UnrotateVector(Velocity); RelativeVelocity.Normalize();

		if (RelativeVelocity.IsNormalized() && RelativeVelocity.Length() > 0.0f)
		{
			/* Reset direction every frame */
			Direction = EDirection::None;
		
			/* Moving up */
			if (RelativeVelocity.X > 0.25)
			{
				Direction |= EDirection::Up;
			}
			/* Moving down */
			else if (RelativeVelocity.X < -0.25)
			{
				Direction |= EDirection::Down;
			}

			/* Moving right */
			if (RelativeVelocity.Y > 0.25)
			{
				Direction |= EDirection::Right;
			}
			/* Moving left */
			else if (RelativeVelocity.Y < -0.25)
			{
				Direction |= EDirection::Left;
			}
		}
		UpdateFlipbook();
	}
}

/* Updates the flipbook of the flipbook component based on character direction */
void ACustomerCharacter::UpdateFlipbook()
{
	UPaperFlipbook* NewFlipbook = nullptr;
	
	/* If the customer is moving */
	if (IsMoving())
	{
		/* Return if a data table entry wasn't found */
		if (!CustomerWalkingInfo) return;

		/* Assign flipbooks based on direction */
		switch (Direction)
		{
		case EDirection::None:
			NewFlipbook = CustomerIdleInfo->Down;
			break;
		case EDirection::Up:
			NewFlipbook = CustomerWalkingInfo->Up;
			break;
		case EDirection::Down:
			NewFlipbook = CustomerWalkingInfo->Down;
			break;
		case EDirection::Left:
			NewFlipbook = CustomerWalkingInfo->Left;
			break;
		case EDirection::Right:
			NewFlipbook = CustomerWalkingInfo->Right;
			break;
		case EDirection::UpLeft:
			NewFlipbook = CustomerWalkingInfo->UpLeft;
			break;
		case EDirection::UpRight:
			NewFlipbook = CustomerWalkingInfo->UpRight;
			break;
		case EDirection::DownLeft:
			NewFlipbook = CustomerWalkingInfo->DownLeft;
			break;
		case EDirection::DownRight:
			NewFlipbook = CustomerWalkingInfo->DownRight;
			break;
		default:
			NewFlipbook = nullptr;
		}
	}
	/* If the customer is standing still */
	else
	{
		/* Return if a data table entry wasn't found */
		if (!CustomerIdleInfo) return;

		/* Assign flipbooks based on direction */
		switch (Direction)
		{
		case EDirection::None:
			NewFlipbook = CustomerIdleInfo->Down;
			break;
		case EDirection::Up:
			NewFlipbook = CustomerIdleInfo->Up;
			break;
		case EDirection::Down:
			NewFlipbook = CustomerIdleInfo->Down;
			break;
		case EDirection::Left:
			NewFlipbook = CustomerIdleInfo->Left;
			break;
		case EDirection::Right:
			NewFlipbook = CustomerIdleInfo->Right;
			break;
		case EDirection::UpLeft:
			NewFlipbook = CustomerIdleInfo->UpLeft;
			break;
		case EDirection::UpRight:
			NewFlipbook = CustomerIdleInfo->UpRight;
			break;
		case EDirection::DownLeft:
			NewFlipbook = CustomerIdleInfo->DownLeft;
			break;
		case EDirection::DownRight:
			NewFlipbook = CustomerIdleInfo->DownRight;
			break;
		default:
			NewFlipbook = nullptr;
		}
	}
	/* Assign flipbook variable to the flipbook component */
	FlipbookComponent->SetFlipbook(NewFlipbook);
}

/* Initialises default variables */
void ACustomerCharacter::Setup(FString Name)
{
	/* If customer character info data table found, assign contents of rows to structs */
	if (CustomerCharacterInfoDataTable)
	{
		static const FString ContextString(TEXT("Customer Character Info Context"));
		CustomerIdleInfo = CustomerCharacterInfoDataTable->FindRow<FCharacterInfo>(FName(Name + "_Idle"), ContextString, true);
		CustomerWalkingInfo = CustomerCharacterInfoDataTable->FindRow<FCharacterInfo>(FName(Name + "_Walking"), ContextString, true);
	}

	UpdateFlipbook();

	/* If customer modifier info data table found, assign contents of row to struct */
	if (CustomerModifierInfoDataTable)
	{
		static const FString ContextString(TEXT("Customer Modifier Info Context"));
		CustomerModifierInfo = CustomerModifierInfoDataTable->FindRow<FCustomerModifierInfo>(FName(Name), ContextString, true);
	}

	/* Set modifier property from modifier struct */
	if (CustomerModifierInfo)
	{
		Modifier |= CustomerModifierInfo->FirstModifier;
		Modifier |= CustomerModifierInfo->SecondModifier;
	}
}

