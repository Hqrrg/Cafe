// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACafeCharacter::ACafeCharacter()
{
}

/* Called when actor is spawned */
void ACafeCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Add input mapping context */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

/* Setup input component */
void ACafeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/* Bind movement input logic */
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACafeCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACafeCharacter::Idle);
	}
}

/* Movement input logic */
void ACafeCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		SetMoving(true);
		
		/* Find yaw rotation */
		FRotator Rotation = Controller->GetControlRotation();
		FRotator Yaw = FRotator(0.0f, Rotation.Yaw, 0.0f);

		/* Find axis vectors */
		const FVector ForwardVector = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);

		/* Add movement input for both axis vectors */
		AddMovementInput(ForwardVector, MovementVector.Y);
		AddMovementInput(RightVector, MovementVector.X);

		/* Reset direction every input */
		Direction = EDirection::None;

		/* Moving up */
		if (MovementVector.Y > 0)
		{
			Direction |= EDirection::Up;
		}
		/* Moving down */
		else if (MovementVector.Y < 0)
		{
			Direction |= EDirection::Down;
		}
		
		/* Moving right */
		if (MovementVector.X > 0)
		{
			Direction |= EDirection::Right;
		}
		/* Moving left */
		else if (MovementVector.X < 0)
		{
			Direction |= EDirection::Left;
		}
		
		UpdateFlipbook();
	}
}

void ACafeCharacter::Idle()
{
	SetMoving(false);
	UpdateFlipbook();
}
