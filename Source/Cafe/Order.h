// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "UObject/Object.h"
#include "Order.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTicketUpdated, UPARAM(ref) TArray<EIngredient>,  Ingredients);

UCLASS()
class CAFE_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	UOrder();

public:
	FORCEINLINE void Set(TArray<EIngredient> Ingredients) { OrderArray = Ingredients; }

	void AddIngredientToTicket(EIngredient Ingredient);

	void ClearTicket();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsFulfilled();

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EIngredient> GetTicketArray() { return TicketArray; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EIngredient> GetOrderArray() { return OrderArray; }

	UPROPERTY(BlueprintAssignable)
	FTicketUpdated OnTicketUpdated;
	
private:
	UPROPERTY()
	TArray<EIngredient> TicketArray;
	
	UPROPERTY()
	TArray<EIngredient> OrderArray;
};