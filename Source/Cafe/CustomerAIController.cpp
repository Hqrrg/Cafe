// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomerAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Navigation/PathFollowingComponent.h"


/* Sets default values */
ACustomerAIController::ACustomerAIController()
{
	/* Disable tick for this actor to improve performance */
	PrimaryActorTick.bCanEverTick = false;

	/* Find and assign behaviour tree to component */
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviourTreeAsset(TEXT("/Game/Cafe/Blueprints/AI/BT_Customer.BT_Customer"));
	if (BehaviourTreeAsset.Succeeded())
	{
		BehaviorTree = BehaviourTreeAsset.Object;
	}

	GetPathFollowingComponent()->SetStopMovementOnFinish(false);
}

/* Run behaviour tree when possessing a pawn */
void ACustomerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
