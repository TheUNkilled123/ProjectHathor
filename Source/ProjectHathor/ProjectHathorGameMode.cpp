// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectHathorGameMode.h"
#include "ProjectHathorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectHathorGameMode::AProjectHathorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
