// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Order.h"
#include "OrderRegister.generated.h"

UCLASS()
class CAFE_API AOrderRegister : public AActor, public IInteractable, public FOrder
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrderRegister();

protected:
	void Interact_Implementation();

public:	

};
