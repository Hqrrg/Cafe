// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

/* Sets default  values for this actors properties */
ACafeCharacter::ACafeCharacter()
{
	/* Configure capsule component to the appropriate size */
	GetCapsuleComponent()->SetCapsuleSize(24.0f, 100.0f, true);

	/* Configure movement speeds */
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.0f;

	/* Configure flipbook component transform, taking into account vertical scale for the orthographic camera */
	FlipbookComponent = GetSprite();
	FlipbookComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	FlipbookComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.141f));
}

/* Update the flipbook of the flipbook component */
void ACafeCharacter::UpdateFlipbook()
{
}

/* Set the direction property and update flipbook */
void ACafeCharacter::SetDirection(EDirection NewDirection)
{
	Direction = NewDirection;
	UpdateFlipbook();
}

/* Set the moving property and update flipbook */
void ACafeCharacter::SetMoving(bool Is)
{
	Moving = Is;
	UpdateFlipbook();
}
