// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "InputActionValue.h"
#include "Inventory.h"
#include "Order.h"
#include "Engine/DataTable.h"
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

public:
	/* Sets default values for this actor's properties */
	ABaristaCharacter();
	
protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PossessedBy(AController* NewController) override;;

	virtual void UnPossessed() override;

	/* Setup input component */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void UpdateFlipbook() override;
	
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

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE UInventory* GetInventory() { return Inventory; }

	FORCEINLINE void SetInventory(UInventory* NewInventory) { Inventory = NewInventory;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE UOrder* GetCurrentOrder() { return CurrentOrder; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ACustomerCharacter* GetCurrentCustomerRef() { return CurrentCustomerRef; }

private:
	UFUNCTION()
	void CustomerBeginOrder(class ACustomerCharacter* OrderingCustomer);
	
private:
	UPROPERTY()
	class ACafeGameModeBase* GameModeRef = nullptr;

	UPROPERTY()
	class ACustomerCharacter* CurrentCustomerRef = nullptr;

	UPROPERTY()
	UInventory* Inventory = nullptr;

	UPROPERTY()
	UOrder* CurrentOrder = nullptr;
	
	/* Return true if line trace hits an actor and set by reference */
	bool LineTraceFromMousePosition(FHitResult& HitResult);

	FHitResult* OutHit = new FHitResult();
	bool LineTrace;

	UPROPERTY()
	UDataTable* BaristaCharacterInfoDataTable = nullptr;
	
	FCharacterInfo* BaristaIdleInfo;
	FCharacterInfo* BaristaWalkingInfo;
};
