// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCharacter.h"

#include "CharacterNavigationBox.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

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
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		/* Get mouse cursor screen coordinates */
		float MouseX, MouseY; PlayerController->GetMousePosition(MouseX, MouseY);

		/* Max length of the line trace */
		const int32 MAX_TRACE_DIST = 1000;

		/* Get camera info */
		FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		FVector CameraDirection = CameraRotation.Vector().GetSafeNormal();

		/* Get trace start & end locations in the world from the mouse position */
		FVector TraceStartLoc, TraceEndLoc;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, TraceStartLoc, CameraDirection);
		TraceEndLoc = TraceStartLoc + MAX_TRACE_DIST * CameraDirection;

		FHitResult* OutHit = new FHitResult();
		FCollisionQueryParams QueryParams;

		/* Line Trace */
		bool LineTrace = GetWorld()->LineTraceSingleByChannel(
			*OutHit,
			TraceStartLoc,
			TraceEndLoc,
			ECC_Visibility,
			QueryParams
		);

		/* If it finds nothing, return */
		if (!LineTrace) return;
		
		FVector PlayerLocation = GetActorLocation();
		FVector TargetLocation = OutHit->Location;
		FVector WorldDirection = UKismetMathLibrary::GetDirectionUnitVector(PlayerLocation, TargetLocation);

		/* Prospective next location should the player keep moving towards target */
		FVector NextLocation = PlayerLocation + WorldDirection * 10;

		if (NavigationBox)
		{
			/* If the next location would be out of bounds, do not continue */
			if (!NavigationBox->IsLocationWithinArea(NextLocation))
			{
				Idle();
				return;
			}
		}
		/* Move towards target location */
		AddMovementInput(WorldDirection, 1.0f);
		
		SetMoving(GetVelocity().Length() > 0);

		/* Get player velocity in relation to the player */
		FRotator Rotation = GetControlRotation();
		FVector Velocity = GetVelocity();
		FVector RelativeVelocity = Rotation.UnrotateVector(Velocity); RelativeVelocity.Normalize();

		if (RelativeVelocity.IsNormalized())
		{
			/* Reset direction every input */
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

void ACafeCharacter::Idle()
{
	SetMoving(false);
	UpdateFlipbook();
}
