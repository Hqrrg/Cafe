// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.h"
#include "Order.generated.h"

USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<EIngredient> TicketArray;
	
	UPROPERTY()
	TArray<EIngredient> OrderArray;

public:
	FOrder() {}

	FOrder(TArray<EIngredient> Ingredients)
	{
		OrderArray = Ingredients;
	}

	void AddIngredientToTicket(EIngredient Ingredient)
	{
		TicketArray.Add(Ingredient);
	}

	void ClearTicket()
	{
		TicketArray.Empty();
	}
	
	bool IsFulfilled()
	{
		if (TicketArray.Num() != OrderArray.Num()) return false;

		bool Fulfilled = true;
		
		for (int i = 0; i < TicketArray.Num(); i++)
		{
			if (TicketArray[i] != OrderArray[i])
			{
				Fulfilled = false;
				break;
			}
		}
		
		return Fulfilled;
	}
};