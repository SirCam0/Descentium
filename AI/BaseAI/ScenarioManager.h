// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums/Scenario.h"
#include "ScenarioManager.generated.h"

UCLASS()
class DESCENTIUM_API AScenarioManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AScenarioManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FScenario> Stage1Scenarios;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FScenario> Stage2Scenarios;
	
	TArray<FScenario> UnUsedStage1Scenarios;

	TArray<FScenario> UnUsedStage2Scenarios;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ShuffleScenarios();

	UFUNCTION(BlueprintCallable)
	void ResetUnUsedScenarios();
	
	FScenario GetStage1Scenario();
	FScenario GetStage2Scenario();
};
