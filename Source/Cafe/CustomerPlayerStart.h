// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "CustomerPlayerStart.generated.h"

UCLASS()
class CAFE_API ACustomerPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	/* Getter for SpawnDirection */
	FORCEINLINE EDirection GetSpawnDirection() { return SpawnDirection; }
	
private:
	/* Direction the customer should face when spawning */
	UPROPERTY(EditInstanceOnly, Category = "Defaults")
	EDirection SpawnDirection = EDirection::None;
};
