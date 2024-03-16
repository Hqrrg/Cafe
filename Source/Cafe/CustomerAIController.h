// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomerAIController.generated.h"

UCLASS()
class CAFE_API ACustomerAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
	
public:
	/* Sets default values for this actor's properties */
	ACustomerAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
