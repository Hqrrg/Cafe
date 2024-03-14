// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CafePlayerController.generated.h"

class ACafeCamera;
/**
 * 
 */
UCLASS()
class CAFE_API ACafePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/* Called when actor is spawned */
	virtual void BeginPlay() override;
	
	/* Called when possessing a pawn */
	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION(BlueprintSetter) /* Sets the player's camera */
	void SetCafeCamera(ACafeCamera* Camera);
	
private:
	UPROPERTY()
	ACafeCamera* CafeCamera = nullptr;
};
