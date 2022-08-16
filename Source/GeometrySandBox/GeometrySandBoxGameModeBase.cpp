// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandBoxGameModeBase.h"

#include "Core/Public/SandBoxPawn.h"

AGeometrySandBoxGameModeBase::AGeometrySandBoxGameModeBase()
{
	DefaultPawnClass = ASandBoxPawn::StaticClass();
	
}
