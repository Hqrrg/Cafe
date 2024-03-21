// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Station.h"
#include "CoffeeStation.generated.h"

UCLASS()
class CAFE_API ACoffeeStation : public AStation
{
	GENERATED_BODY()
	// Sets default values for this pawn's properties
public:
	ACoffeeStation();

protected:
	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;
};
