// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "Ingredient.h"
#include "InputActionValue.h"
#include "Order.h"
#include "Engine/DataTable.h"
#include "BaristaCharacter.generated.h"


USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

public:
	FInventory()
	{
		UIngredient* Water = NewObject<UIngredient>(); Water->Setup(FName("Water"));
		UIngredient* CoffeeBeans = NewObject<UIngredient>(); CoffeeBeans->Setup(FName("Coffee Beans"));
		UIngredient* Milk = NewObject<UIngredient>(); Milk->Setup(FName("Milk"));
		UIngredient* SoyMilk = NewObject<UIngredient>(); SoyMilk->Setup(FName("Soy Milk"));
		UIngredient* AlmondMilk = NewObject<UIngredient>(); SoyMilk->Setup(FName("Almond Milk"));
		UIngredient* CaramelSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Caramel Syrup"));
		UIngredient* HazelnutSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Hazelnut Syrup"));
		UIngredient* GingerbreadSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Gingerbread Syrup"));

		Ingredients.Add(EIngredient::Water, Water);
		Ingredients.Add(EIngredient::CoffeeBeans, CoffeeBeans);
		Ingredients.Add(EIngredient::Milk, Milk);
		Ingredients.Add(EIngredient::SoyMilk, SoyMilk);
		Ingredients.Add(EIngredient::AlmondMilk, AlmondMilk);
		Ingredients.Add(EIngredient::CaramelSyrup, CaramelSyrup);
		Ingredients.Add(EIngredient::HazelnutSyrup, HazelnutSyrup);
		Ingredients.Add(EIngredient::GingerbreadSyrup, GingerbreadSyrup);	
	}
	
public:
	UIngredient* GetIngredient(EIngredient Key)
	{
		return *Ingredients.Find(Key);
	}
	
private:
	UPROPERTY()
	TMap<EIngredient, UIngredient*> Ingredients = TMap<EIngredient, UIngredient*>();
};

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
	FORCEINLINE FInventory& GetInventory() { return *Inventory; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FOrder& GetCurrentOrder() { return *CurrentOrder; }

private:
	UFUNCTION()
	void CustomerBeginOrder(class ACustomerCharacter* OrderingCustomer);
	
private:
	UPROPERTY()
	class ACafeGameModeBase* GameModeRef = nullptr;
	
	FInventory* Inventory;

	FOrder* CurrentOrder;
	
	/* Return true if line trace hits an actor and set by reference */
	bool LineTraceFromMousePosition(FHitResult& HitResult);

	FHitResult* OutHit = new FHitResult();
	bool LineTrace;

	UPROPERTY()
	UDataTable* BaristaCharacterInfoDataTable = nullptr;
	
	FCharacterInfo* BaristaIdleInfo;
	FCharacterInfo* BaristaWalkingInfo;
};
