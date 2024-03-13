// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CafeCameraManager.h"
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
	/* Called when spawning a player controller */
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

public:
	UFUNCTION(BlueprintGetter) /* Get the camera manager */
	FORCEINLINE ACafeCameraManager* GetCameraManager() { return CameraManager; }
		
private:
	UPROPERTY()
	ACafeCameraManager* CameraManager = nullptr;
};
