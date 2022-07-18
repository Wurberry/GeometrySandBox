// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
	
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	SetColor(GeometryData.Color);
	
	// Prints
	//PrintTypes();
	//PrintStringTypes();
	//PrintTransform();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
	
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			float Time = GetWorld()->GetTimeSeconds();
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
			SetActorLocation(CurrentLocation);
			break;
		}
	case EMovementType::Static:
		{
			break;
		}
	default: break;
	}
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogTemp, Display, TEXT("Hello Unreal"));
	
	UE_LOG(LogTemp, Display, TEXT("Weapons Number - %d - %i, Health - %f, is Dead - %d"),
		WeaponsNum, WeaponsNum, Health, IsDead);

}

void ABaseGeometryActor::PrintStringTypes()
{
	
	FString Name = "John Connor";
	FString StrWeaponsNum = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString StrHealth = "Health count = " + FString::SanitizeFloat(Health);
	FString StrIsDead = "Is Dead - " + FString(IsDead ? "trueee" : "falseeee");

	FString Stat = FString::Printf(TEXT("All Stat \n %s \n %s \n %s"), *StrWeaponsNum, *StrHealth, *StrIsDead);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name,true, FVector2D(1.5f,1.5f));

}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotator = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogTemp, Warning, TEXT("Actor Name - %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Transform - %s"), *Transform.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Location - %s"), *Location.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Rotator - %s"), *Rotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Scale - %s"), *Scale.ToString());
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if(DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}
