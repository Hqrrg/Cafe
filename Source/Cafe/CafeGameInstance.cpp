// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeGameInstance.h"

void UCafeGameInstance::LoadDefaults()
{
	SetDay(0);
	SetBalance(50.0f);
	SetProfitQuota(0.0f);
	SetBaristaInventory(NewObject<UInventory>());
}
