// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CineCameraComponent.h"
#include "GameFramework/Actor.h"
#include "CafeCamera.generated.h"

UCLASS(NotBlueprintable)
class CAFE_API ACafeCamera : public AActor
{
	GENERATED_BODY()

	/* Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCineCameraComponent* CameraComponent;

public:
	// Sets default values for this actor's properties
	ACafeCamera();

public:
	/* Set the owning player of this actor */
	FORCEINLINE void SetOwningPlayer(APlayerController* Player) { OwningPlayer = Player; }

private:
	UPROPERTY()
	APlayerController* OwningPlayer;
};
