// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySandBox/Core/Public/GeometryHubActor.h"


// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	FirstLoopGenerator();
	SecondLoopGenerator();
	ThirdLoopGenerator();
	
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGeometryHubActor::FirstLoopGenerator()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for(int32 i = 0; i<10; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 300.0f));
			ABaseGeometryActor* GeometryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if(GeometryActor)
			{
				FGeometryData Data;
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				GeometryActor->SetGeometryData(Data);
			}
		}	
	}
}

void AGeometryHubActor::SecondLoopGenerator()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for(int32 i = 0; i<10; i++)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 300.0f * i, 700.0f));
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);

			if(GeometryActor)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				GeometryActor->SetGeometryData(Data);
				GeometryActor->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::ThirdLoopGenerator()
{
	UWorld* World = GetWorld();
	if(World)
	{
		for(const FGeometryPayLoad PayLoad : GeometryPayLoads)
		{
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(PayLoad.GeometryClass, PayLoad.InitialTransform);
			if(GeometryActor)
			{
				GeometryActor->SetGeometryData(PayLoad.Data);
				GeometryActor->FinishSpawning(PayLoad.InitialTransform);
			}
			
		}
	}
}
