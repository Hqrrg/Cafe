// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeQueueManager.h"


/* Sets defaut values for this actor */
ACafeQueueManager::ACafeQueueManager()
{
	/* Disable tick for this actor to improve performance */
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);
}

/* Called when this actor is spawned */
void ACafeQueueManager::BeginPlay()
{
	Super::BeginPlay();
}
