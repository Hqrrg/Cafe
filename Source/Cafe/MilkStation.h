// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Station.h"
#include "MilkStation.generated.h"

UCLASS()
class CAFE_API AMilkStation : public AStation
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMilkStation();

protected:
	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;
};
