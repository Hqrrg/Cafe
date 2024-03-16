// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "GameFramework/Actor.h"
#include "CafeQueueManager.generated.h"

/* Custom vector type that includes "Occupied" boolean */
USTRUCT(BlueprintType)
struct  FQueuePoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = false, EditConditionHides = true))
	bool Occupied;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDirection Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MakeEditWidget = true))
	FVector Location;
};

UCLASS()
class CAFE_API ACafeQueueManager : public AActor
{
	GENERATED_BODY()

	/* Root Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

public:
	/* Sets default values for this actor */
	ACafeQueueManager();

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FQueuePoint GetQueuePoint(int32 Index);

	UFUNCTION(BlueprintPure)
	bool IsQueuePointOccupied(FQueuePoint QueuePoint);

	UFUNCTION(BlueprintPure)
	EDirection GetQueuePointDirection(FQueuePoint QueuePoint);

	UFUNCTION(BlueprintPure)
	FVector GetQueuePointWorldLocation(FQueuePoint QueuePoint);

public:
	/* Array of queue points that comprise the queue */
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Defaults", DisplayName = "Queue Points");
	TArray<FQueuePoint> QueuePointArray;
};
