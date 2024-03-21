// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "UObject/Object.h"
#include "Order.generated.h"

UCLASS()
class CAFE_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	UOrder();

public:
	FORCEINLINE void Set(TArray<EIngredient> Ingredients) { OrderArray = Ingredients; }

	FORCEINLINE void AddIngredientToTicket(EIngredient Ingredient) { TicketArray.Add(Ingredient); }

	FORCEINLINE void ClearTicket() { TicketArray.Empty(); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsFulfilled();

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EIngredient> GetTicketArray() { return TicketArray; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EIngredient> GetOrderArray() { return OrderArray; }
	
private:
	UPROPERTY()
	TArray<EIngredient> TicketArray;
	
	UPROPERTY()
	TArray<EIngredient> OrderArray;
};