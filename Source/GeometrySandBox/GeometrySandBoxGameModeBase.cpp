// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandBoxGameModeBase.h"

#include "Core/Public/SandBoxPawn.h"
#include "Core/Public/SandBoxPlayerController.h"

AGeometrySandBoxGameModeBase::AGeometrySandBoxGameModeBase()
{
	DefaultPawnClass = ASandBoxPawn::StaticClass();
	PlayerControllerClass = ASandBoxPlayerController::StaticClass();
}
