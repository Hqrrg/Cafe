// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "GameFramework/Pawn.h"
#include "Station.generated.h"

/* Enum for make inputs */
UENUM(BlueprintType)
enum class EMakeKey : uint8
{
	None = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};

UCLASS()
class CAFE_API AStation : public APawn, public IInteractable
{
	GENERATED_BODY()

	/* Input Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	/* Make Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MakeAction;

	/* Exit Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ExitAction;

public:
	/* Sets default values for this actors properties */
	AStation();

protected:
	/* Called when pawn is possessed */
	virtual void PossessedBy(AController* NewController) override;

	/* Called when pawn is unpossessed */
	virtual void UnPossessed() override;
	
	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/* Make input logic */
	void Make(const FInputActionValue& Value);

	/* Exit input logic */
	void Exit(const FInputActionValue& Value);

public:
	/* Interact behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void Interact_Implementation() override;

	/* Selection behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void Selected_Implementation(bool Is) override;

	/* Setter for InteractedPawn ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;

protected:
	bool DoesInputMatchIngredient();

protected:
	/* Array for station's ingredients to be stored in */
	UPROPERTY()
	TArray<EIngredient> IngredientArray;

	/* Barista reference, set when interacting */
	UPROPERTY()
	class ABaristaCharacter* BaristaRef;

	/* Array of inputs */
	UPROPERTY()
	TArray<EMakeKey> InputArray;
};
