// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Station.h"
#include "SyrupStation.generated.h"

UCLASS()
class CAFE_API ASyrupStation : public AStation
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASyrupStation();

protected:
	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;
};
