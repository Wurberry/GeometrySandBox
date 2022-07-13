// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	PrintTypes();
	PrintStringTypes();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogTemp, Display, TEXT("Hello Unreal"));

	int WeaponsNum = 4;
	float Health = 34.32134f;
	bool IsDead = false;

	UE_LOG(LogTemp, Display, TEXT("Weapons Number - %d - %i, Health - %f, is Dead - %d"),
		WeaponsNum, WeaponsNum, Health, IsDead);

}

void ABaseGeometryActor::PrintStringTypes()
{
	int WeaponsNum = 4;
	float Health = 34.32134f;
	bool IsDead = false;
	
	FString Name = "John Connor";
	FString StrWeaponsNum = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString StrHealth = "Health count = " + FString::SanitizeFloat(Health);
	FString StrIsDead = "Is Dead - " + FString(IsDead ? "trueee" : "falseeee");

	FString Stat = FString::Printf(TEXT("All Stat \n %s \n %s \n %s"), *StrWeaponsNum, *StrHealth, *StrIsDead);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name,true, FVector2D(1.5f,1.5f));

}
