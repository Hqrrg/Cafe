// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterNavigationBox.h"

#include "CafeCharacter.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"


// Sets default values
ACharacterNavigationBox::ACharacterNavigationBox()
{
	// Disable tick for this actor to improve performance
	PrimaryActorTick.bCanEverTick = false;

	NavigationBox = CreateDefaultSubobject<UBoxComponent>(TEXT("NavigationBox"));
	NavigationBox->SetupAttachment(RootComponent);
}

void ACharacterNavigationBox::BeginPlay()
{
	Super::BeginPlay();

	FVector Center = NavigationBox->Bounds.GetBox().GetCenter();
	FVector Size = NavigationBox->Bounds.GetBox().GetSize();
	FVector Size2D = FVector(Size.X, Size.Y, 0.0f) / 2;
	FVector PointA = Center - Size2D;
	FVector PointB = Center + Size2D;
	
	float MinX = FMath::Min(PointA.X, PointB.X);
	float MinY = FMath::Min(PointA.Y, PointB.Y);
	MinLocation = FVector(MinX, MinY, 0.0f);
	
	float MaxX = FMath::Max(PointA.X, PointB.X);
	float MaxY = FMath::Max(PointA.Y, PointB.Y);
	MaxLocation = FVector(MaxX, MaxY, 0.0f);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *MinLocation.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *MaxLocation.ToString()));
	
}

bool ACharacterNavigationBox::IsLocationWithinArea(FVector& Location)
{
	bool WithinX = MinLocation.X <= Location.X && MaxLocation.X >= Location.X;
	bool WithinY = MinLocation.Y <= Location.Y && MaxLocation.Y >= Location.Y;

	return WithinX && WithinY;
}

