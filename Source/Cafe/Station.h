// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Interactable.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "Station.generated.h"

enum class EIngredient : uint8;
enum class EMakeKey: uint8;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMakeInput, UPARAM(ref) TArray<EMakeKey>, Inputs);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMakeIngredient, EIngredient, Ingredient);

UCLASS()
class CAFE_API AStation : public APawn, public IInteractable
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetComponent = nullptr;
	
	/* Input Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	/* Make Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ClearAction;

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


	/* Clear input logic */
	void Clear(const FInputActionValue& Value);
	
	/* Exit input logic */
	void Exit(const FInputActionValue& Value);

public:
	/* Interact behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void Interact_Implementation() override;

	/* Selection behaviour ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void Selected_Implementation(bool Is) override;

	/* Setter for InteractedPawn ~ _Impementation suffix because of BlueprintNativeEvent */
	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;

	bool ShouldBeNextTo_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnIngredientMade(EIngredient Ingredient);

	UPROPERTY(BlueprintAssignable)
	FMakeIngredient OnMakeIngredient;

	UFUNCTION(BlueprintImplementableEvent)
	void OnExit();

	UPROPERTY(BlueprintAssignable)
	FMakeInput OnMakeInput;

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ABaristaCharacter* GetBaristaRef() { return BaristaRef; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EIngredient> GetIngredientArray() { return IngredientArray; }

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
