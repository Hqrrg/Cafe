// Fill out your copyright notice in the Description page of Project Settings.


#include "BaristaCharacter.h"

#include "CharacterNavigationBox.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactable.h"
#include "Kismet/KismetMathLibrary.h"


/* Called when actor is spawned */
void ABaristaCharacter::BeginPlay()
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
void ABaristaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/* Bind movement input logic */
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaristaCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABaristaCharacter::Idle);

		/* Bind interact input logic */
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ABaristaCharacter::Interact);
	}
}

/* Movement input logic */
void ABaristaCharacter::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		FHitResult* OutHit = new FHitResult();
		bool LineTrace = LineTraceFromMousePosition(*OutHit);
		
		/* If line trace finds nothing, return */
		if (!LineTrace) return;
		
		FVector PlayerLocation = GetActorLocation();
		FVector TargetLocation = OutHit->Location; TargetLocation = FVector(TargetLocation.X, TargetLocation.Y, PlayerLocation.Z);
		FVector WorldDirection = UKismetMathLibrary::GetDirectionUnitVector(PlayerLocation, TargetLocation);

		/* Prospective next location should the player keep moving towards target */
		constexpr uint32 BUFFER = 10;
		FVector NextLocation = PlayerLocation + WorldDirection * BUFFER;

		if (NavigationBox)
		{
			/* If the next location would be out of bounds, do not continue */
			if (!NavigationBox->IsLocationWithinArea(NextLocation))
			{
				Idle();
				return;
			}
		}

		float DistanceToTarget = (TargetLocation - PlayerLocation).Length();
		float ScaleValue = FMath::GetMappedRangeValueClamped(FVector2D(10.0f, 5.0f), FVector2D(1.0f, 0.0f), DistanceToTarget);
		
		/* Move towards target location */
		AddMovementInput(WorldDirection, ScaleValue);
		
		SetMoving(GetVelocity().Length() > 0.0f);

		/* Get player velocity in relation to the player */
		FRotator Rotation = GetControlRotation();
		FVector Velocity = GetVelocity();
		FVector RelativeVelocity = Rotation.UnrotateVector(Velocity); RelativeVelocity.Normalize();

		if (RelativeVelocity.IsNormalized() && RelativeVelocity.Length() > 0.0f)
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

void ABaristaCharacter::Idle()
{
	SetMoving(false);
	UpdateFlipbook();
}

void ABaristaCharacter::Interact(const FInputActionValue& Value)
{
	if (Controller)
	{
		FHitResult* OutHit = new FHitResult();
		bool LineTrace = LineTraceFromMousePosition(*OutHit);

		if (!LineTrace) return;

		if (AActor* HitActor = OutHit->GetActor())
		{
			if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
			{
				/* Execute interact function on the interactable actor */
				IInteractable::Execute_Interact(HitActor);

				/* If we were not worrying about BlueprintNativeEvent
				 * the function call would look like this: Interactable->Interact(); */
			}
		}
	}
}

/* Return true if line trace hits an actor and set by reference */
bool ABaristaCharacter::LineTraceFromMousePosition(FHitResult& OutHit)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		/* Get mouse cursor screen coordinates */
		float MouseX, MouseY; PlayerController->GetMousePosition(MouseX, MouseY);

		/* Max length of the line trace */
		const int32 MAX_TRACE_DIST = 5000;

		/* Get camera info */
		FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		FVector CameraDirection = CameraRotation.Vector().GetSafeNormal();

		/* Get trace start & end locations in the world from the mouse position */
		FVector TraceStartLoc, TraceEndLoc;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, TraceStartLoc, CameraDirection);
		TraceEndLoc = TraceStartLoc + MAX_TRACE_DIST * CameraDirection;
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		
		/* Line Trace */
		bool LineTrace = GetWorld()->LineTraceSingleByChannel(
			OutHit,
			TraceStartLoc,
			TraceEndLoc,
			ECC_Visibility,
			QueryParams
		);

		return LineTrace;
	}
	return false;
}
