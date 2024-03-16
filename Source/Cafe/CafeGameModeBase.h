// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CafeCameraManager.h"
#include "CafeQueueManager.h"
#include "GameFramework/GameModeBase.h"
#include "CafeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CAFE_API ACafeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/* Set default values */
	ACafeGameModeBase();

protected:
	/* Called when game starts */
	virtual void BeginPlay() override;
	
	/* Called when spawning a player controller */
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

	/* Called when spawning default pawn into the world */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

public:
	UFUNCTION(BlueprintPure) /* Get the camera manager */
	FORCEINLINE ACafeCameraManager* GetCameraManager() { return CameraManager; }

	UFUNCTION(BlueprintPure) /* Get the queue manager */
	FORCEINLINE ACafeQueueManager* GetQueueManager() { return QueueManager; }
	
private:
	UPROPERTY()
	ACafeCameraManager* CameraManager = nullptr;

	UPROPERTY()
	ACafeQueueManager* QueueManager = nullptr;
};
