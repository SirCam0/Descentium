// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "A3DNavMesh.generated.h"

UCLASS()
class DESCENTIUM_API AA3DNavMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA3DNavMesh();

	UPROPERTY()
	USceneComponent* root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Bounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resolution = 100;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector Extent = FVector(1000);

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> Locations;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> ValidLocations;

	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> InvalidLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShowDebug;

	UFUNCTION(BlueprintImplementableEvent)
	void BuildNavigation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FVector> GetValidLocations();

};
