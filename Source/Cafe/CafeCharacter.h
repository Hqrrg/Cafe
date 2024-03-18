// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "PaperCharacter.h"
#include "Engine/DataTable.h"
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

/* DataTable struct containing flipbook information for CafeCharacters */
USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Up;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Down;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Left;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* Right;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* UpLeft;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* UpRight;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* DownLeft;

	UPROPERTY(EditAnywhere)
	UPaperFlipbook* DownRight;
};

UCLASS()
class CAFE_API ACafeCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this actors properties */
	ACafeCharacter();

protected:
	/* Update the flipbook of the flipbook component */
	virtual void UpdateFlipbook();

public:
	/* Getter for character direction */
	UFUNCTION(BlueprintPure)
	FORCEINLINE EDirection GetDirection() { return Direction; }

	/* Setter for character direction */
	UFUNCTION(BlueprintCallable)
	void SetDirection(EDirection NewDirection);

	/* Getter for character movement state */
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsMoving() { return Moving; }
	
	/* Setter for character movement state */
	UFUNCTION(BlueprintCallable)
	void SetMoving(bool Is);
	
protected:
	UPROPERTY()
	UPaperFlipbookComponent* FlipbookComponent;
	
	EDirection Direction = EDirection::None;
	bool Moving = false;
};
