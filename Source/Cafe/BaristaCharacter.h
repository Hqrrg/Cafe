// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "InputActionValue.h"
#include "BaristaCharacter.generated.h"

UCLASS()
class CAFE_API ABaristaCharacter : public ACafeCharacter
{
	GENERATED_BODY()

	/* InputMappingContext */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	/* Move InputAction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/* Interact InputAction */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

	/* Setup input component */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	/* Movement input logic */
	void Move(const FInputActionValue& Value);

	/* Movement has ended */
	void Idle();

	/* Interact input logic */
	void Interact(const FInputActionValue& Value);

public:
	/* Optional navigation bounds */
	UPROPERTY(EditInstanceOnly)
	class ACharacterNavigationBox* NavigationBox;

private:
	/* Return true if line trace hits an actor and set by reference */
	bool LineTraceFromMousePosition(FHitResult& OutHit);
};
