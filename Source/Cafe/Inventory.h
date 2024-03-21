// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "UObject/Object.h"
#include "Inventory.generated.h"


UCLASS()
class CAFE_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UInventory();
	
public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE UIngredient* GetIngredient(EIngredient Key) { return *Ingredients.Find(Key); }
	
private:
	UPROPERTY()
	TMap<EIngredient, UIngredient*> Ingredients;
};
