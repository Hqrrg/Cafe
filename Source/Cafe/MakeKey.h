// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MakeKey.generated.h"

/* Enum for make inputs */
UENUM(BlueprintType)
enum class EMakeKey : uint8
{
	None = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};
