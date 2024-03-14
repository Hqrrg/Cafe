// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class CAFE_API IInteractable
{
	GENERATED_BODY()

public:
	/* Overridable function which can be implemented in blueprints
	 * Called when a subclass is interacted with
	 * Not "Virtual" because of BlueprintNativeEvent */
	UFUNCTION(BlueprintNativeEvent)
	void Interact();
	
	 /* Overridable function which can be implemented in blueprints
	 * Called when a subclass is selected or deselected
	 * Not "Virtual" because of BlueprintNativeEvent */
	UFUNCTION(BlueprintNativeEvent)
	void Selected(bool Is);
};
