// Copyright Epic Games, Inc. All Rights Reserved.

#include "CosmicInterrogationGameMode.h"
#include "CosmicInterrogationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACosmicInterrogationGameMode::ACosmicInterrogationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
