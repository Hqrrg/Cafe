// Fill out your copyright notice in the Description page of Project Settings.


#include "Order.h"

UOrder::UOrder()
{
}

void UOrder::AddIngredientToTicket(EIngredient Ingredient)
{
	if (TicketArray.Num() < 7)
	{
		TicketArray.Add(Ingredient);
		OnTicketUpdated.Broadcast(TicketArray);
	}
}

void UOrder::ClearTicket()
{
	TicketArray.Empty();
	OnTicketUpdated.Broadcast(TicketArray);
}

bool UOrder::IsFulfilled()
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
