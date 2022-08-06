// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySandBox/Core/Public/GeometryHubActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogaHubGeometry, All, All);

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

	 
	// FirstLoopGenerator();
	// SecondLoopGenerator();
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
				GeometryActor->OnColorChange.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				GeometryActor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				GeometryActor->FinishSpawning(PayLoad.InitialTransform);
			}
			
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogaHubGeometry, Warning, TEXT("Actor name - %s, Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogaHubGeometry, Error, TEXT("Timer finished %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if(!Geometry) return;

	Geometry->Destroy();
	//Geometry->SetLifeSpan(2.0f);
}


