// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CafeCameraManager.h"
#include "CafeQueueManager.h"
#include "GameFramework/GameModeBase.h"
#include "CafeGameModeBase.generated.h"


enum class EOrderSatisfaction : uint8;

/* Customer Rarity Enum */
UENUM(BlueprintType)
enum ECustomerRarity : uint8
{
	Rare = 0,
	Uncommon = 2,
	Common = 4
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomerOrdered, class ACustomerCharacter*, Customer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomerLeft, class ACustomerCharacter*, Customer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCustomerOrderConcluded, class ACustomerCharacter*, Customer, EOrderSatisfaction, OrderSatisfaction);

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

	UFUNCTION()
	void RemoveCustomer(class ACustomerCharacter* Customer);

private:
	UFUNCTION() /* Spawn a customer character */
	void SpawnCustomer(FTransform SpawnTransform, EDirection SpawnDirection);

public:
	/* Default map of customer names with an associated customer rarity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customers")
	TMap<FString, TEnumAsByte<ECustomerRarity>> DefaultCustomerMap;

	/* Customer Ordered Event Dispatcher */
	UPROPERTY(BlueprintAssignable)
	FCustomerOrdered OnCustomerBeginOrder;

	/* Customer MakeOrder Concluded Event Dispatcher */
	UPROPERTY(BlueprintAssignable)
	FCustomerOrderConcluded OnCustomerEndOrder;
	
	
private:
	UPROPERTY() /* Camera Manager */
	ACafeCameraManager* CameraManager = nullptr;

	UPROPERTY() /* Queue Manager */
	ACafeQueueManager* QueueManager = nullptr;

	UPROPERTY() /* Customer Instance Array */
	TArray<class ACustomerCharacter*> CustomerArray;

	/* TimerHandle for spawning customers */
	FTimerHandle SpawnCustomerTimerHandle;
};
