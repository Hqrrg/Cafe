// Fill out your copyright notice in the Description page of Project Settings.


#include "Station.h"

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
	// void CheckArray();
	
	/* Debug */
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Magenta, FString::Printf(TEXT("%i"), MakeKey));
	
}

/* Exit input logic */
void AStation::Exit(const FInputActionValue& Value)
{
	/* Repossess InteractedPawn (Barista) */
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->Possess(InteractedPawn);
}

/* Interact behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
void AStation::Interact_Implementation()
{
	IInteractable::Interact_Implementation();

	/* Possess this pawn */
	APlayerController* PlayerController = Cast<APlayerController>(InteractedPawn->GetController());
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

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *Pawn->GetName()));
	InteractedPawn = Pawn;
}

