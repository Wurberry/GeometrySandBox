// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChange, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float Frequency = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Design")
	float TimerRate = 1.0f;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	// UPROPERTIES
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGeometryData GetGeometryData() const {return GeometryData;}

	UPROPERTY(BlueprintAssignable)
	FOnColorChange OnColorChange;
	FOnTimerFinished OnTimerFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// UPROPERTIES
	// count of weapons that pawn can have

	UPROPERTY(EditAnywhere, Category = "Geometry Data")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 AmmoNum = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float Health = 34.32134f;

	UPROPERTY(EditInstanceOnly, Category = "Stats")
	bool IsDead = false;

private:
	
	FVector InitialLocation;
	FTimerHandle TimerHandle;
	const int32 MaxTimerCount = 5;
	int32 TimerCount;
	
	void HandleMovement();
	
	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();

	void SetColor(const FLinearColor& Color);

	void OnTimerFired();
};
