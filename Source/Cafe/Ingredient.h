// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "Ingredient.generated.h"

enum class EMakeKey : uint8;

USTRUCT(BlueprintType)
struct FIngredientInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Texture;

	UPROPERTY(EditAnywhere)
	TArray<EMakeKey> Pattern;

	UPROPERTY(EditAnywhere)
	float Price = 0.0f;
};

UENUM(BlueprintType)
enum class EIngredient : uint8
{
	Water = 0,
	CoffeeBeans,
	Milk,
	SoyMilk,
	AlmondMilk,
	CaramelSyrup,
	HazelnutSyrup,
	GingerbreadSyrup
};

UENUM(BlueprintType)
enum class EIngredientUseResult : uint8
{
	NoStock = 0,
	Success = 1
};

UCLASS()
class CAFE_API UIngredient : public UObject
{
	GENERATED_BODY()

public:
	UIngredient();
	
public:
	UIngredient* Setup(FName Name);
	
	EIngredientUseResult Use();
	
public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE uint8 GetQuantity() { return Quantity; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuantity(uint8 Value) { Quantity = Value; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UTexture2D* GetTexture() { return Texture; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<EMakeKey> GetMakeKeyPattern() { return MakeKeyPattern; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetPrice() { return Price; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetIngredientName() { return IngredientName; }

private:
	UPROPERTY()
	UTexture2D* Texture;

	UPROPERTY()
	TArray<EMakeKey> MakeKeyPattern;
	
	UPROPERTY()
	float Price = 0.0f;

	UPROPERTY()
	uint8 Quantity = 1;

	UPROPERTY()
	FName IngredientName;

	UPROPERTY()
	class UDataTable* IngredientDataTable = nullptr;
	
	FIngredientInfo* IngredientInfo;
	
};
