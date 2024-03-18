// Fill out your copyright notice in the Description page of Project Settings.


#include "BaristaCharacter.h"

#include "CharacterNavigationBox.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactable.h"
#include "Kismet/KismetMathLibrary.h"


/* Sets default values for this actors properties */
ABaristaCharacter::ABaristaCharacter()
{
	/* Find and assign barista character info data table */
	static ConstructorHelpers::FObjectFinder<UDataTable> BaristaCharacterInfoDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_BaristaCharacterInfo.DT_BaristaCharacterInfo"));
	if (BaristaCharacterInfoDataTableAsset.Succeeded())
	{
		BaristaCharacterInfoDataTable = BaristaCharacterInfoDataTableAsset.Object;
	}

	/* If found, assign contents of rows to structs */
	if (BaristaCharacterInfoDataTable)
	{
		static const FString ContextString(TEXT("Barista Character Info Context"));
		BaristaIdleInfo = BaristaCharacterInfoDataTable->FindRow<FCharacterInfo>(FName("Idle"), ContextString, true);
		BaristaWalkingInfo = BaristaCharacterInfoDataTable->FindRow<FCharacterInfo>(FName("Walking"), ContextString, true);
	}
}

/* Called when actor is spawned */
void ABaristaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaristaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Controller)
	{
		OutHit = new FHitResult();
		LineTrace = LineTraceFromMousePosition(*OutHit);
	}
}

void ABaristaCharacter::PossessedBy(AController* NewController)
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

void ABaristaCharacter::UnPossessed()
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

/* Updates the flipbook of the flipbook component based on character direction */
void ABaristaCharacter::UpdateFlipbook()
{
	UPaperFlipbook* NewFlipbook = nullptr;;

	/* If the player is moving */
	if (IsMoving())
	{
		/* Return if a data table entry wasn't found */
		if (!BaristaWalkingInfo) return;

		/* Assign flipbooks based on direction */
		switch (Direction)
		{
			case EDirection::None:
				NewFlipbook = BaristaWalkingInfo->Down;
				break;
			case EDirection::Up:
				NewFlipbook = BaristaWalkingInfo->Up;
				break;
			case EDirection::Down:
				NewFlipbook = BaristaWalkingInfo->Down;
				break;
			case EDirection::Left:
				NewFlipbook = BaristaWalkingInfo->Left;
				break;
			case EDirection::Right:
				NewFlipbook = BaristaWalkingInfo->Right;
				break;
			case EDirection::UpLeft:
				NewFlipbook = BaristaWalkingInfo->UpLeft;
				break;
			case EDirection::UpRight:
				NewFlipbook = BaristaWalkingInfo->UpRight;
				break;
			case EDirection::DownLeft:
				NewFlipbook = BaristaWalkingInfo->DownLeft;
				break;
			case EDirection::DownRight:
				NewFlipbook = BaristaWalkingInfo->DownRight;
				break;
			default:
				NewFlipbook = nullptr;
		}
	}
	/* If the player is standing still */
	else
	{
		/* Return if a data table entry wasn't found */
		if (!BaristaIdleInfo) return;

		/* Assign flipbooks based on direction */
		switch (Direction)
		{
			case EDirection::None:
				NewFlipbook = BaristaIdleInfo->Down;
				break;
			case EDirection::Up:
				NewFlipbook = BaristaIdleInfo->Up;
				break;
			case EDirection::Down:
				NewFlipbook = BaristaIdleInfo->Down;
				break;
			case EDirection::Left:
				NewFlipbook = BaristaIdleInfo->Left;
				break;
			case EDirection::Right:
				NewFlipbook = BaristaIdleInfo->Right;
				break;
			case EDirection::UpLeft:
				NewFlipbook = BaristaIdleInfo->UpLeft;
				break;
			case EDirection::UpRight:
				NewFlipbook = BaristaIdleInfo->UpRight;
				break;
			case EDirection::DownLeft:
				NewFlipbook = BaristaIdleInfo->DownLeft;
				break;
			case EDirection::DownRight:
				NewFlipbook = BaristaIdleInfo->DownRight;
				break;
			default:
				NewFlipbook = nullptr;
		}
	}
	/* Assign flipbook variable to the flipbook component */
	FlipbookComponent->SetFlipbook(NewFlipbook);
}

/* Movement input logic */
void ABaristaCharacter::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
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

/* Called when the player is standing still */
void ABaristaCharacter::Idle()
{
	SetMoving(false);
	UpdateFlipbook();
}

/* Called when the player presses the interact input key */
void ABaristaCharacter::Interact(const FInputActionValue& Value)
{
	if (Controller)
	{
		/* If the line trace found nothing, return */
		if (!LineTrace) return;

		if (AActor* HitActor = OutHit->GetActor())
		{
			if ((GetActorLocation() - HitActor->GetActorLocation()).Length() <= 100.0f)
			{
				/* If the line trace hit an actor that implements IInteractable */
				if (IInteractable* Interactable = Cast<IInteractable>(HitActor))
				{
					/* Set InteractedPawn on the interactable actor */
					IInteractable::Execute_SetInteractedPawn(HitActor, this);
					
					/* Execute interact function on the interactable actor */
					IInteractable::Execute_Interact(HitActor);

					/* If we were not worrying about BlueprintNativeEvent
					 * the function call would look like this: Interactable->Interact(); */
				}
			}
		}
	}
}

/* Return true if line trace hits an actor and set by reference */
bool ABaristaCharacter::LineTraceFromMousePosition(FHitResult& HitResult)
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
		bool LineTraceFromMousePos = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			TraceStartLoc,
			TraceEndLoc,
			ECC_Visibility,
			QueryParams
		);

		return LineTraceFromMousePos;
	}
	return false;
}
