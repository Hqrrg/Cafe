// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "Ingredient.h"

UInventory::UInventory()
{
	UIngredient* Water = NewObject<UIngredient>(); Water->Setup(FName("Water"));
	UIngredient* CoffeeBeans = NewObject<UIngredient>(); CoffeeBeans->Setup(FName("Coffee Beans"));
	UIngredient* Milk = NewObject<UIngredient>(); Milk->Setup(FName("Milk"));
	UIngredient* SoyMilk = NewObject<UIngredient>(); SoyMilk->Setup(FName("Soy Milk"));
	UIngredient* AlmondMilk = NewObject<UIngredient>(); SoyMilk->Setup(FName("Almond Milk"));
	UIngredient* CaramelSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Caramel Syrup"));
	UIngredient* HazelnutSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Hazelnut Syrup"));
	UIngredient* GingerbreadSyrup = NewObject<UIngredient>(); SoyMilk->Setup(FName("Gingerbread Syrup"));

	Ingredients.Add(EIngredient::Water, Water);
	Ingredients.Add(EIngredient::CoffeeBeans, CoffeeBeans);
	Ingredients.Add(EIngredient::Milk, Milk);
	Ingredients.Add(EIngredient::SoyMilk, SoyMilk);
	Ingredients.Add(EIngredient::AlmondMilk, AlmondMilk);
	Ingredients.Add(EIngredient::CaramelSyrup, CaramelSyrup);
	Ingredients.Add(EIngredient::HazelnutSyrup, HazelnutSyrup);
	Ingredients.Add(EIngredient::GingerbreadSyrup, GingerbreadSyrup);
}
