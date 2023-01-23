// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NonDoorSpawnLocation.generated.h"

UCLASS()
class DESCENTIUM_API ANonDoorSpawnLocation : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANonDoorSpawnLocation();

	USceneComponent* Root;
	
	AActor* CurrentActor = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
