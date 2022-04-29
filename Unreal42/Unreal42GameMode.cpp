// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal42GameMode.h"
#include "Unreal42Character.h"
#include "UObject/ConstructorHelpers.h"

AUnreal42GameMode::AUnreal42GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
