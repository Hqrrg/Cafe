// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Order.h"
#include "Bin.generated.h"

UCLASS()
class CAFE_API ABin : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABin();

protected:
	virtual void Interact_Implementation() override;

	virtual void SetInteractedPawn_Implementation(APawn* Pawn) override;

private:
	UPROPERTY()
	class ABaristaCharacter* BaristaRef = nullptr;

};
