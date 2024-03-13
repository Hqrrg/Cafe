// Fill out your copyright notice in the Description page of Project Settings.


#include "CafeCamera.h"


/* Sets default values */
ACafeCamera::ACafeCamera()
{
	/* Disable tick for this actor to improve performance */
	PrimaryActorTick.bCanEverTick = false;

	/* Create camera component and set as root */
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	SetRootComponent(CameraComponent);
}

