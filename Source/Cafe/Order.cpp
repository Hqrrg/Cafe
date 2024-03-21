// Fill out your copyright notice in the Description page of Project Settings.


#include "Order.h"

UOrder::UOrder()
{
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
