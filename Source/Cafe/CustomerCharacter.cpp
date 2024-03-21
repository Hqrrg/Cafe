// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerCharacter.h"

#include "CafeGameModeBase.h"
#include "CustomerAIController.h"
#include "Ingredient.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"


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

	GameModeRef = Cast<ACafeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	UpdateFlipbook();
}

void ACustomerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		if (!GameModeRef) return;
		
		GameModeRef->GetQueueManager()->SetQueuePointOccupied(QueuePointIndex, false);
	}
	Super::EndPlay(EndPlayReason);
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

	
	const float CAPSULE_BOUNDS_PADDING = 5.0f;
	/* Scaling fix for disproportionate sprites */
	for (float Scale = 1.0f; Scale > 0.0f; Scale-=0.01f)
	{
		FVector FlipbookBounds = FlipbookComponent->Bounds.BoxExtent;
		FVector CapsuleBounds = GetCapsuleComponent()->Bounds.BoxExtent + FVector(CAPSULE_BOUNDS_PADDING, CAPSULE_BOUNDS_PADDING, CAPSULE_BOUNDS_PADDING);

		if (FlipbookBounds.Length() > CapsuleBounds.Length())
		{
			FlipbookComponent->SetRelativeScale3D(FVector(Scale, Scale, Scale * 1.414f));	
		}
		else break;
	}

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

	ApplyModifiers();
	GenerateOrder();
}

void ACustomerCharacter::ApplyModifiers()
{
	switch (Modifier)
	{
		case ECustomerModifier::Normal:
			break;
		case ECustomerModifier::Rushing:
			OrderTimerDuration = 20.0f;
			break;
		case ECustomerModifier::Grumpy:
			ToleratedAttempts = 1;
			break;
		case ECustomerModifier::Generous:
			MaxTipMultiplier = 2;
			break;
		case ECustomerModifier::Snob:
			OrderLength = FMath::RandRange(5, 7);
			break;

		case ECustomerModifier::RushingGrumpy:
			OrderTimerDuration = 20.0f;
			ToleratedAttempts = 1;
			break;
		case ECustomerModifier::RushingGenerous:
			OrderTimerDuration = 20.0f;
			MaxTipMultiplier = 2;
			break;
		case ECustomerModifier::RushingSnob:
			OrderTimerDuration = 20.0f;
			OrderLength = FMath::RandRange(5, 7);
			break;
		case ECustomerModifier::GrumpyGenerous:
			ToleratedAttempts = 1;
			MaxTipMultiplier = 2;
			break;
		case ECustomerModifier::GrumpySnob:
			ToleratedAttempts = 1;
			OrderLength = FMath::RandRange(5, 7);
			break;
		case ECustomerModifier::GenerousSnob:
			MaxTipMultiplier = 2;
			OrderLength = FMath::RandRange(5, 7);
			break;
	default:
		break;
	}
}

void ACustomerCharacter::GenerateOrder()
{
	TArray<EIngredient> Ingredients;

	Ingredients.Add(EIngredient::Water);
	Ingredients.Add(EIngredient::CoffeeBeans);
	Ingredients.Add(EIngredient::Milk);
	Ingredients.Add(EIngredient::AlmondMilk);
	Ingredients.Add(EIngredient::SoyMilk);
	Ingredients.Add(EIngredient::CaramelSyrup);
	Ingredients.Add(EIngredient::HazelnutSyrup);
	Ingredients.Add(EIngredient::GingerbreadSyrup);
	
	TArray<EIngredient> OrderIngredients;

	OrderIngredients.Add(EIngredient::Water);
	OrderIngredients.Add(EIngredient::CoffeeBeans);
	
	for (int i = 0; i < OrderLength - 2; i++)
	{
		const uint32 IngredientIndex = FMath::RandRange(0, Ingredients.Num()-1);
		
		EIngredient Ingredient = Ingredients[IngredientIndex];

		OrderIngredients.Add(Ingredient);
	}
	
	OrderIngredients.Sort([](const EIngredient A, const EIngredient B) { return A < B; });

	Order = NewObject<UOrder>(); Order->Set(OrderIngredients);
}

void ACustomerCharacter::MakeOrder()
{
	if (!GameModeRef) return;
	
	GameModeRef->OnCustomerBeginOrder.Broadcast(this);
	
	GetWorldTimerManager().SetTimer(OrderTimerHandle, this, &ACustomerCharacter::ConcludeOrder, OrderTimerDuration, true);
}

void ACustomerCharacter::ConcludeOrder()
{
	EOrderSatisfaction OrderSatisfaction = EOrderSatisfaction::Good;
	
	FTimerManager& TimerManager = GetWorldTimerManager();
	
	if (TimerManager.TimerExists(OrderTimerHandle))
	{
		TimerManager.PauseTimer(OrderTimerHandle);
	}
	
	const float TimeElapsed = FMath::Clamp(TimerManager.GetTimerElapsed(OrderTimerHandle), 0.0f, OrderTimerDuration);
	
	const float TipMultiplier = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, OrderTimerDuration), FVector2D(MaxTipMultiplier, 0.0f), TimeElapsed);
	const float TipAmount = MaxTipAmount * TipMultiplier;
	
	Destroy();
	
	GameModeRef->RemoveCustomer(this);

	if (TipMultiplier > MaxTipMultiplier * 0.8)
	{
		OrderSatisfaction = EOrderSatisfaction::Excellent;
	}
	else if (TipMultiplier > MaxTipMultiplier * 0.6)
	{
		OrderSatisfaction = EOrderSatisfaction::VeryGood;
	}
	else if (TipMultiplier > MaxTipMultiplier * 0.4)
	{
		OrderSatisfaction = EOrderSatisfaction::Good;
	}
	else if (TipMultiplier > MaxTipMultiplier * 0.2)
	{
		OrderSatisfaction = EOrderSatisfaction::Poor;
	}
	else if (TipMultiplier > 0.0f)
	{
		OrderSatisfaction = EOrderSatisfaction::VeryPoor;
	}

	GameModeRef->OnCustomerEndOrder.Broadcast(this, TipAmount, OrderSatisfaction);
}

