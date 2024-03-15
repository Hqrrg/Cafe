// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACafeCharacter::ACafeCharacter()
{
	GetCapsuleComponent()->SetCapsuleSize(24.0f, 100.0f, true);
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.0f;
}
