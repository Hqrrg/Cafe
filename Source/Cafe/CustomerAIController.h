// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomerAIController.generated.h"

UCLASS()
class CAFE_API ACustomerAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	/* Sets default values for this actor's properties */
	ACustomerAIController();

protected:
	/* Called when possessing a pawn */
	virtual void OnPossess(APawn* InPawn) override;

private:
	/* Behaviour tree property */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
};
