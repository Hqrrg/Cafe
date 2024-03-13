// Copyright Epic Games, Inc. All Rights Reserved.


#include "CafeGameModeBase.h"

#include "CafeCharacter.h"

ACafeGameModeBase::ACafeGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ACafeCharacter> DefaultPawn(TEXT("/Game/Cafe/Blueprints/BP_Barista"));

	if (DefaultPawn.Succeeded())
	{
		DefaultPawnClass = DefaultPawn.Class;
	}
}
