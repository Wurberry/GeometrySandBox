// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySandBox/Core/Public/SandBoxPlayerController.h"
#include "Components/InputComponent.h"
#include "GeometrySandBox/Core/Public/SandBoxPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSBPlayerController, All, All);

void ASandBoxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandBoxPlayerController::ChangePawn);
	}
}

void ASandBoxPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandBoxPawn::StaticClass(), Pawns);
	
}

void ASandBoxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;

	ASandBoxPawn* CurrentPawn = Cast<ASandBoxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (!CurrentPawn) return;
	Possess(CurrentPawn);
	UE_LOG(LogSBPlayerController, Warning, TEXT("Change pawn"));
	
	
}
