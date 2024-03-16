// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACafeCharacter::ACafeCharacter()
{
	GetCapsuleComponent()->SetCapsuleSize(24.0f, 100.0f, true);
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.0f;

	FlipbookComponent = GetSprite();
	FlipbookComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	FlipbookComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.828f));
}

void ACafeCharacter::UpdateFlipbook()
{
}

void ACafeCharacter::SetDirection(EDirection NewDirection)
{
	Direction = NewDirection;
	UpdateFlipbook();
}

void ACafeCharacter::SetMoving(bool Is)
{
	Moving = Is;
	UpdateFlipbook();
}
