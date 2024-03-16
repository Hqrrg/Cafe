// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"

#include "CustomerAIController.h"


// Sets default values
ACustomerCharacter::ACustomerCharacter()
{
	/* Disable tick for this actor to improve performance */
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = ACustomerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;

	static ConstructorHelpers::FObjectFinder<UDataTable> CustomerCharacterInfoDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_CustomerCharacterInfo.DT_CustomerCharacterInfo"));
	if (CustomerCharacterInfoDataTableAsset.Succeeded())
	{
		CustomerCharacterInfoDataTable = CustomerCharacterInfoDataTableAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> CustomerModifierInfoDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_CustomerModifierInfo.DT_CustomerModifierInfo"));
	if (CustomerModifierInfoDataTableAsset.Succeeded())
	{
		CustomerModifierInfoDataTable = CustomerModifierInfoDataTableAsset.Object;
	}
}

// Called when the game starts or when spawned
void ACustomerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateFlipbook();
}

void ACustomerCharacter::UpdateFlipbook()
{
	UPaperFlipbook* NewFlipbook = nullptr;

	if (IsMoving())
	{
		if (!CustomerWalkingInfo) return;
		
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
	else
	{
		if (!CustomerIdleInfo) return;
		
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
	FlipbookComponent->SetFlipbook(NewFlipbook);
}

void ACustomerCharacter::Setup(FString Name)
{
	if (CustomerCharacterInfoDataTable)
	{
		static const FString ContextString(TEXT("Customer Character Info Context"));
		CustomerIdleInfo = CustomerCharacterInfoDataTable->FindRow<FCharacterInfo>(FName(Name + "_Idle"), ContextString, true);
		CustomerWalkingInfo = CustomerCharacterInfoDataTable->FindRow<FCharacterInfo>(FName(Name + "_Walking"), ContextString, true);
	}

	UpdateFlipbook();

	if (CustomerModifierInfoDataTable)
	{
		static const FString ContextString(TEXT("Customer Modifier Info Context"));
		CustomerModifierInfo = CustomerModifierInfoDataTable->FindRow<FCustomerModifierInfo>(FName(Name), ContextString, true);
	}

	if (CustomerModifierInfo)
	{
		Modifier |= CustomerModifierInfo->FirstModifier;
		Modifier |= CustomerModifierInfo->SecondModifier;
	}
}

