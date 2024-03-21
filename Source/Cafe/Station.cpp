// Fill out your copyright notice in the Description page of Project Settings.


#include "Station.h"

#include "MakeKey.h"
#include "Ingredient.h"
#include "BaristaCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


/* Set default values for this actors properties */
AStation::AStation()
{
	/* Disable tick for this actor */
	PrimaryActorTick.bCanEverTick = false;
}

/* Called when pawn is possessed */
void AStation::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/* Add input mapping context */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

/* Called when pawn is unpossessed */
void AStation::UnPossessed()
{
	Super::UnPossessed();

	/* Remove input mapping context */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
}

/* Called to bind functionality to input */
void AStation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/* Bind make input logic */
		EnhancedInputComponent->BindAction(MakeAction, ETriggerEvent::Triggered, this, &AStation::Make);

		/* Bind exit input logic */
		EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Triggered, this, &AStation::Exit);
	}
}

/* Make input logic */
void AStation::Make(const FInputActionValue& Value)
{
	/* Input vector */
	FVector2D MakeVector = Value.Get<FVector2D>();

	EMakeKey MakeKey = EMakeKey::None;

	/* W */
	if (MakeVector.Y > 0.0f)
	{
		MakeKey = EMakeKey::Up;
	}
	/* S */
	else if (MakeVector.Y < 0.0f)
	{
		MakeKey = EMakeKey::Down;
	}
	/* D */
	if (MakeVector.X > 0.0f)
	{
		MakeKey = EMakeKey::Right;
	}
	/* A */
	else if (MakeVector.X < 0.0f)
	{
		MakeKey = EMakeKey::Left;
	}

	/* We can then add MakeKey to an array */
	InputArray.Add(MakeKey);

	/* Clear input array if input matches ingredient pattern */
	if (DoesInputMatchIngredient()) InputArray.Empty();
}

/* Exit input logic */
void AStation::Exit(const FInputActionValue& Value)
{
	/* Reset inputs */
	InputArray.Empty();
	
	/* Repossess InteractedPawn (Barista) */
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->Possess(BaristaRef);
}

/* Interact behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
void AStation::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	/* Possess this pawn */
	APlayerController* PlayerController = Cast<APlayerController>(BaristaRef->GetController());
	PlayerController->Possess(this);
}

/* Selection behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
void AStation::Selected_Implementation(bool Is)
{
	IInteractable::Selected_Implementation(Is);
}

/* Setter for InteractedPawn ~ _Impementation suffix because of BlueprintNativeEvent */
void AStation::SetInteractedPawn_Implementation(APawn* Pawn)
{
	IInteractable::SetInteractedPawn_Implementation(Pawn);
	
	BaristaRef = Cast<ABaristaCharacter>(Pawn);

	IngredientArray.Add(EIngredient::CoffeeBeans);
}

bool AStation::DoesInputMatchIngredient()
{
	EIngredient MatchedIngredientKey = EIngredient::Water;
	UIngredient* MatchedIngredient = nullptr;

	/* Loop through this stations ingredients */
	for (EIngredient Key : IngredientArray)
	{
		UIngredient* Ingredient = BaristaRef->GetInventory()->GetIngredient(Key);
		
		/* Get pattern of ingredient */
		TArray<EMakeKey> IngredientPattern = Ingredient->GetMakeKeyPattern();
		
		bool Match = true;

		/* If the input array length does not equal the ingredient pattern length then continue to next iteration */
		if (InputArray.Num() != IngredientPattern.Num()) continue;

		/* Loop through each element in input array */
		for (int i = 0; i < InputArray.Num(); i++)
		{
			/* Compare to ingredient pattern, if there's an inconsistency then break the loop */
			if (InputArray[i] != IngredientPattern[i])
			{
				Match = false;
				break;
			}
		}
		/* If input array loop finished with a perfect match then set MatchedIngredient */
		if (Match)
		{
			MatchedIngredientKey = Key;
			MatchedIngredient = Ingredient;
			break;
		}
	}

	if (MatchedIngredient)
	{
		/* Attempt to use matched ingredient */
		EIngredientUseResult UseResult = MatchedIngredient->Use();
		
		if (UseResult == EIngredientUseResult::Success)
		{
			BaristaRef->GetCurrentOrder()->AddIngredientToTicket(MatchedIngredientKey);
		}
	}
	return MatchedIngredient ? true : false;
}

