// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaristaCharacter.h"
#include "Engine/GameInstance.h"
#include "CafeGameInstance.generated.h"

UCLASS()
class CAFE_API UCafeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBaristaInventory(UInventory* Inventory) { BaristaInventory = Inventory; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UInventory* GetBaristaInventory() { return BaristaInventory; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetDay() { return Day; }

	UFUNCTION()
	FORCEINLINE void SetDay(int32 Value) { Day = Value; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetProfitQuota() { return ProfitQuota; }

	UFUNCTION()
	FORCEINLINE void SetProfitQuota(float Value) { ProfitQuota = Value; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetBalance() { return Balance; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBalance(float Value) { Balance = Value; }
	
private:
	UPROPERTY()
	UInventory* BaristaInventory = NewObject<UInventory>();
	
	int32 Day = 0;
	float Balance = 100.0f;
	float ProfitQuota = 0.0f;
};
