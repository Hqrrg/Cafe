// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CafeCameraManager.generated.h"

class ACafeCamera;

/*
 * Enum for use as camera map keys
 * Possibility for more cameras in future
*/
UENUM(BlueprintType)
enum class ECameraView : uint8
{
	Default
};

/* Empty actor that contains a map of all cafe cameras currently instanced in the level */
UCLASS(NotBlueprintable)
class CAFE_API ACafeCameraManager : public AActor
{
	GENERATED_BODY()

public:
	/* Sets default values */
	ACafeCameraManager();

public:
	UFUNCTION(BlueprintPure) /* Retrieve camera from map */
	FORCEINLINE ACafeCamera* GetCamera(ECameraView Key) { return *CafeCameraMap.Find(Key); }
	
private:
	/* Map of cafe camera's with enum values as unique keys, editable on an instance */
	UPROPERTY(EditInstanceOnly, Category = "Defaults", DisplayName = "Cameras")
	TMap<ECameraView, ACafeCamera*> CafeCameraMap;
};
