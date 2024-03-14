// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterNavigationBox.generated.h"

UCLASS(NotBlueprintable)
class CAFE_API ACharacterNavigationBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* NavigationBox;

public:
	// Sets default values for this actor's properties
	ACharacterNavigationBox();

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

public:
	bool IsLocationWithinArea(FVector& Location);

private:
	UPROPERTY()
	FVector MinLocation;

	UPROPERTY()
	FVector MaxLocation;
};
