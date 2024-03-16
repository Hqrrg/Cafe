// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CafeCharacter.h"
#include "Engine/DataTable.h"
#include "CustomerCharacter.generated.h"

/* Bitflag Enum: more info https://www.youtube.com/watch?v=TuHFeS_eBe8 */
UENUM(NotBlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ECustomerModifier : uint16
{
	Normal				= 0b00000000, // 0
	Rushing				= 0b00000001, // 1
	Grumpy				= 0b00000010, // 2
	Generous			= 0b00000100, // 4
	Snob				= 0b00001000, // 8

	RushingGrumpy		= Rushing | Grumpy		UMETA(Hidden), // 3
	RushingGenerous		= Rushing | Generous	UMETA(Hidden), // 5
	RushingSnob			= Rushing | Snob		UMETA(Hidden), // 9
	GrumpyGenerous 		= Grumpy | Generous		UMETA(Hidden), // 6
	GrumpySnob 			= Grumpy | Snob			UMETA(Hidden), // 10
	GenerousSnob 		= Generous | Snob		UMETA(Hidden) // 12
};
ENUM_CLASS_FLAGS(ECustomerModifier);

USTRUCT(BlueprintType)
struct FCustomerModifierInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECustomerModifier FirstModifier = ECustomerModifier::Normal;

	UPROPERTY(EditAnywhere)
	ECustomerModifier SecondModifier = ECustomerModifier::Normal;
};

UCLASS()
class CAFE_API ACustomerCharacter : public ACafeCharacter
{
	GENERATED_BODY()

public:
	/* Sets default properties for this actor */
	ACustomerCharacter();

protected:
	/* Called when this actor is spawned */
	virtual void BeginPlay() override;

	virtual void UpdateFlipbook() override;

public:
	void Setup(FString Name);
	
	/* Getter for customer characteristic */
	UFUNCTION(BlueprintPure)
	FORCEINLINE ECustomerModifier GetModifier() { return Modifier; }
	
private:
	ECustomerModifier Modifier = ECustomerModifier::Normal;

	UPROPERTY()
	UDataTable* CustomerCharacterInfoDataTable = nullptr;

	FCharacterInfo* CustomerIdleInfo = nullptr;
	FCharacterInfo* CustomerWalkingInfo = nullptr;

	UPROPERTY()
	UDataTable* CustomerModifierInfoDataTable = nullptr;

	FCustomerModifierInfo* CustomerModifierInfo = nullptr;
};
