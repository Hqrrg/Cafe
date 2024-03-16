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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "false", EditConditionHides = "true"))
	bool Occupied = false;

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

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<FVector> GetQueuePoints() { return QueuePointArray; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector GetQueuePoint(int32 Index) { return QueuePointArray[Index]; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector GetQueuePointWorldLocation(int32 Index) { return GetActorLocation() + GetQueuePoint(Index); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsQueuePointOccupied(int32 Index) { return QueuePointInfoArray[Index].Occupied; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool SetQueuePointOccupied(int32 Index, bool Is) { return QueuePointInfoArray[Index].Occupied = Is; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE EDirection GetQueuePointDirection(int32 Index) { return QueuePointInfoArray[Index].Direction; }
	
public:
	/* Array of queue points that comprise the queue */
	UPROPERTY(EditInstanceOnly, Category = "Defaults", DisplayName = "Queue Points", meta = (MakeEditWidget = true))
	TArray<FVector> QueuePointArray;

	UPROPERTY(EditInstanceOnly, Category = "Defaults", DisplayName = "Queue Points Info")
	TArray<FQueuePointInfo> QueuePointInfoArray;
};
