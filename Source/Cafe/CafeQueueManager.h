// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "GameFramework/Actor.h"
#include "CafeQueueManager.generated.h"


USTRUCT(BlueprintType)
struct FQueuePointInfo
{
	GENERATED_BODY()

	/* Whether queue point is occupied by a customer */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "false", EditConditionHides = "true"))
	bool Occupied = false;

	/* Direction the customer should be facing at the queue point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDirection Direction = EDirection::None;
};

UCLASS()
class CAFE_API ACafeQueueManager : public AActor
{
	GENERATED_BODY()

	/* Root Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

public:
	/* Sets default values for this actor */
	ACafeQueueManager();

public:
	UFUNCTION(BlueprintPure) /* Getter for QueuePointArray */
	FORCEINLINE TArray<FVector> GetQueuePoints() { return QueuePointArray; }
	
	UFUNCTION(BlueprintPure) /* Get array element by index from QueuePointArray */
	FORCEINLINE FVector GetQueuePoint(int32 Index) { return QueuePointArray[Index]; }

	UFUNCTION(BlueprintPure) /* Get world location of queue point */
	FORCEINLINE FVector GetQueuePointWorldLocation(int32 Index) { return GetActorLocation() + GetQueuePoint(Index); }

	UFUNCTION(BlueprintPure) /* Return if queue point is occupied by a customer */
	FORCEINLINE bool IsQueuePointOccupied(int32 Index) { return QueuePointInfoArray[Index].Occupied; }

	UFUNCTION(BlueprintCallable) /* Set queue point occupied property */
	FORCEINLINE bool SetQueuePointOccupied(int32 Index, bool Is) { return QueuePointInfoArray[Index].Occupied = Is; }

	UFUNCTION(BlueprintPure) /* Return the direction that the customer should be facing at the queue point */
	FORCEINLINE EDirection GetQueuePointDirection(int32 Index) { return QueuePointInfoArray[Index].Direction; }
	
public:
	/* Array of queue points that comprise the queue */
	UPROPERTY(EditInstanceOnly, Category = "Defaults", DisplayName = "Queue Points", meta = (MakeEditWidget = "true"))
	TArray<FVector> QueuePointArray;

	/* Array of custom queue point info struct that contains information relevant to each queue point in QueuePointArray*/
	UPROPERTY(EditInstanceOnly, Category = "Defaults", DisplayName = "Queue Points Info")
	TArray<FQueuePointInfo> QueuePointInfoArray;
};
