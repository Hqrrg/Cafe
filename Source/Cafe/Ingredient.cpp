// Fill out your copyright notice in the Description page of Project Settings.


#include "Ingredient.h"

UIngredient::UIngredient()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> IngredientDataTableAsset(TEXT("/Game/Cafe/DataTables/DT_IngredientInfo.DT_IngredientInfo"));

	if (IngredientDataTableAsset.Succeeded())
	{
		IngredientDataTable = IngredientDataTableAsset.Object;
	}
}

EIngredientUseResult UIngredient::Use()
{
	if (GetQuantity() > 0)
	{
		SetQuantity(GetQuantity() - 1);
		return EIngredientUseResult::Success;
	}
	return EIngredientUseResult::NoStock;
}

UIngredient* UIngredient::Setup(FName Name)
{
	IngredientName = Name;
	
	if (IngredientDataTable)
	{
		static const FString ContextString(TEXT("Ingredient Info Context"));
		IngredientInfo = IngredientDataTable->FindRow<FIngredientInfo>(Name.ToString().Replace(TEXT(" "), TEXT("_")), ContextString, true);
	}

	if (IngredientInfo)
	{
		Texture = IngredientInfo->Texture;
		MakeKeyPattern = IngredientInfo->Pattern;
		Price = IngredientInfo->Price;
	}
	
	return this;
}
