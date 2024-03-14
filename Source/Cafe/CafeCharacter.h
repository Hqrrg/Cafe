// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "CafeCharacter.generated.h"

/* Bitflag Enum: more info https://www.youtube.com/watch?v=TuHFeS_eBe8 */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EDirection : uint8
{
	None		= 0b00000000, // 0
	Up			= 0b00000001, // 1
	Down		= 0b00000010, // 2
	Left		= 0b00000100, // 4
	Right		= 0b00001000, // 8
	
	UpLeft		= Up | Left, // 5
	UpRight		= Up | Right, // 9
	DownLeft	= Down | Left, // 6
	DownRight	= Down | Right // 10
};
ENUM_CLASS_FLAGS(EDirection);


UCLASS()
class CAFE_API ACafeCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/* InputMappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	/* Move InputAction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

public:
	ACafeCharacter();

protected:
	/* Called when actor is spawned */
	virtual void BeginPlay() override;
	
	/* Setup input component */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	/* Movement input logic */
	void Move(const FInputActionValue& Value);

	/* Movement has ended */
	void Idle();

	/* Update flipbook logic */
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFlipbook();

public:
	/* Getter for character direction */
	UFUNCTION(BlueprintPure)
	FORCEINLINE EDirection GetDirection() { return Direction; }

	/* Getter for character movement state */
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsMoving() { return Moving; }

public:
	UPROPERTY(EditInstanceOnly)
	class ACharacterNavigationBox* NavigationBox;

private:
	/* Setter for character movement state */
	FORCEINLINE void SetMoving(bool Is) { Moving = Is; }
	
private:
	EDirection Direction = EDirection::None;
	bool Moving = false;
};