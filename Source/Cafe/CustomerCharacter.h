// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "Order.h"
#include "Engine/DataTable.h"
#include "CustomerCharacter.generated.h"


/* Bitflag Enum: more info https://www.youtube.com/watch?v=TuHFeS_eBe8 */
UENUM(NotBlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECustomerModifier : uint16
{
	Normal				= 0b00000000, // 0
	Rushing				= 0b00000001, // 1
	Grumpy				= 0b00000010, // 2
	Generous			= 0b00000100, // 4
	Snob				= 0b00001000, // 8

	RushingGrumpy		= Rushing | Grumpy		UMETA(Hidden), // 3
	RushingGenerous		= Rushing | Generous	UMETA(Hidden), // 5
	RushingSnob			= Rushing | Snob		UMETA(Hidden), // 9
	GrumpyGenerous 		= Grumpy | Generous		UMETA(Hidden), // 6
	GrumpySnob 			= Grumpy | Snob			UMETA(Hidden), // 10
	GenerousSnob 		= Generous | Snob		UMETA(Hidden) // 12
};
ENUM_CLASS_FLAGS(ECustomerModifier);

UENUM(BlueprintType)
enum class EOrderSatisfaction : uint8
{
	Excellent,
	VeryGood,
	Good,
	Poor,
	VeryPoor
};

/* DataTable struct containing information about a customer's modifiers */
USTRUCT(BlueprintType)
struct FCustomerModifierInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECustomerModifier FirstModifier = ECustomerModifier::Normal;

	UPROPERTY(EditAnywhere)
	ECustomerModifier SecondModifier = ECustomerModifier::Normal;
};

UCLASS()
class CAFE_API ACustomerCharacter : public ACafeCharacter
{
	GENERATED_BODY()

public:
	/* Sets default properties for this actor */
	ACustomerCharacter();

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;;

	/* Called every frame */
	virtual void Tick(float DeltaSeconds) override;

	/* Update flipbook of flipbook component */
	virtual void UpdateFlipbook() override;

public:
	/* Sets properties from data table */
	void Setup(FString Name);

private:
	void ApplyModifiers();

	void GenerateOrder();
	
public:
	/* Getter for customer characteristic */
	UFUNCTION(BlueprintPure)
	FORCEINLINE ECustomerModifier GetModifier() { return Modifier; }

	/* Get reference to index of queue point customer is occupying */
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetQueuePointIndex() { return QueuePointIndex; }

	/* Set reference to index of queue point customer is occupying */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQueuePointIndex(int32 Index) { QueuePointIndex = Index; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UOrder* GetOrder() { return Order; }

	/* Called when the customer is at the front of the queue */
	UFUNCTION(BlueprintCallable)
	void MakeOrder();

	/* Called when the customer's order is concluded - successfully or not */
	UFUNCTION(BlueprintCallable)
	void ConcludeOrder();
	
private:
	UPROPERTY()
	class ACafeGameModeBase* GameModeRef;
	
	ECustomerModifier Modifier = ECustomerModifier::Normal;

	UPROPERTY()
	UOrder* Order = nullptr;
	
	int32 QueuePointIndex = 0;
	
	FTimerHandle OrderTimerHandle;

	/* MakeOrder Information */
	float OrderTimerDuration = 30.0f;
	float MaxTipAmount = 100.0f;
	int32 MaxTipMultiplier = 1;
	int32 ToleratedAttempts = 3;
	int32 OrderLength = FMath::RandRange(3, 5);

	/* Data Tables & Structs */
	UPROPERTY()
	UDataTable* CustomerCharacterInfoDataTable = nullptr;

	FCharacterInfo* CustomerIdleInfo = nullptr;
	FCharacterInfo* CustomerWalkingInfo = nullptr;

	UPROPERTY()
	UDataTable* CustomerModifierInfoDataTable = nullptr;

	FCustomerModifierInfo* CustomerModifierInfo = nullptr;
};
