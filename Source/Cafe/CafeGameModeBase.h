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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCustomerOrderConcluded, class ACustomerCharacter*, Customer, float, TipAmount, EOrderSatisfaction, OrderSatisfaction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateBalance, float, NewBalance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginDay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndDay, bool, DidMeetQuota);

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

	/* Called every frame */
	virtual void Tick(float DeltaSeconds) override;
	
	/* Called when spawning a player controller */
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

	/* Called when spawning default pawn into the world */
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BeginDay(float LengthSeconds);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndDay(bool DidMeetQuota);
	
public:
	UFUNCTION(BlueprintPure) /* Get the camera manager */
	FORCEINLINE ACafeCameraManager* GetCameraManager() { return CameraManager; }

	UFUNCTION(BlueprintPure) /* Get the queue manager */
	FORCEINLINE ACafeQueueManager* GetQueueManager() { return QueueManager; }

	FORCEINLINE void SetBaristaRef(class ABaristaCharacter* Barista) { BaristaRef = Barista; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE class ABaristaCharacter* GetBaristaRef() { return BaristaRef; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetTimeElapsed() { return TimeElapsed; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetTimeRemaining() { return TimeRemaining; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTimeElapsed(float Value) { TimeElapsed = Value; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTimeRemaining(float Value) { TimeRemaining = Value; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetDay() { return Day; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetBalance() { return Balance; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetQuota() { return Quota; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCustomersDisappointed() { return CustomersDisappointed; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetMaxCustomersDisappointed() { return MaxCustomersDisappointed; }

	UFUNCTION()
	void RemoveCustomer(class ACustomerCharacter* Customer);

private:
	UFUNCTION() /* Spawn a customer character */
	void SpawnCustomer(FTransform SpawnTransform, EDirection SpawnDirection);

	UFUNCTION()
	void AddBalance(class ACustomerCharacter* Customer, float TipAmount, EOrderSatisfaction OrderSatisfaction);

	UFUNCTION()
	void LogCustomerSatisfaction(ACustomerCharacter* Customer, float TipAmount, EOrderSatisfaction OrderSatisfaction);

public:
	/* Default map of customer names with an associated customer rarity */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customers")
	TMap<FString, TEnumAsByte<ECustomerRarity>> DefaultCustomerMap;

	UPROPERTY(BlueprintAssignable)
	FBeginDay OnBeginDay;

	UPROPERTY(BlueprintAssignable)
	FEndDay OnEndDay;
	
	/* Customer Ordered Event Dispatcher */
	UPROPERTY(BlueprintAssignable)
	FCustomerOrdered OnCustomerBeginOrder;

	/* Customer MakeOrder Concluded Event Dispatcher */
	UPROPERTY(BlueprintAssignable)
	FCustomerOrderConcluded OnCustomerEndOrder;

	/* Balance Updated Event Dispatcher */
	UPROPERTY(BlueprintAssignable)
	FUpdateBalance OnUpdateBalance;
	
	
private:
	UPROPERTY() /* Camera Manager */
	ACafeCameraManager* CameraManager = nullptr;

	UPROPERTY() /* Queue Manager */
	ACafeQueueManager* QueueManager = nullptr;

	UPROPERTY()
	class ABaristaCharacter* BaristaRef = nullptr;

	UPROPERTY() /* Customer Instance Array */
	TArray<class ACustomerCharacter*> CustomerArray;

	/* TimerHandle for spawning customers */
	FTimerHandle SpawnCustomerTimerHandle;

	UPROPERTY()
	float TimeElapsed = 0.0f;

	UPROPERTY()
	float TimeRemaining = 0.0f;
	
	UPROPERTY()
	int32 Day = 0;

	UPROPERTY()
	float Balance = 0.0f;
	
	UPROPERTY()
	float Quota = 0.0f;

	int32 MaxCustomersDisappointed = 3;
	int32 CustomersDisappointed = 0;
};
