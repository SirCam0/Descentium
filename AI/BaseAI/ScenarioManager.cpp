// Fill out your copyright notice in the Description page of Project Settings.


#include "ScenarioManager.h"

// Sets default values
AScenarioManager::AScenarioManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScenarioManager::BeginPlay()
{
	Super::BeginPlay();
	ResetUnUsedScenarios();
}

// Called every frame
void AScenarioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScenarioManager::ShuffleScenarios()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Shuffling")));
	if(Stage1Scenarios.Num() > 0)
	{
		int32 LastIndex = Stage1Scenarios.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Stage1Scenarios.Swap(i, Index);
			}
		}
	}
	if(Stage2Scenarios.Num() > 0)
	{
		int32 LastIndex = Stage2Scenarios.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Stage2Scenarios.Swap(i, Index);
			}
		}
	}
}

//Call at the beginning of a run
void AScenarioManager::ResetUnUsedScenarios()
{
	ShuffleScenarios();
	UnUsedStage1Scenarios = Stage1Scenarios;
	UnUsedStage2Scenarios = Stage2Scenarios;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), UnUsedScenarios.Num()));
}

FScenario AScenarioManager::GetStage1Scenario()
{
	
	const int Index = FMath::FRandRange(0,UnUsedStage1Scenarios.Num());
	if(UnUsedStage1Scenarios.IsValidIndex(Index))
	{
		FScenario Scenario = UnUsedStage1Scenarios[Index];
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), Scenario.Waves[0].Enemies[0].Number));
		UnUsedStage1Scenarios.RemoveAt(Index);
		return Scenario;
	}
	FScenario Scenario;
	return Scenario;
}

FScenario AScenarioManager::GetStage2Scenario()
{
	
	const int Index = FMath::FRandRange(0,UnUsedStage2Scenarios.Num());
	if(UnUsedStage2Scenarios.IsValidIndex(Index))
	{
		FScenario Scenario = UnUsedStage2Scenarios[Index];
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), Scenario.Waves[0].Enemies[0].Number));
		UnUsedStage2Scenarios.RemoveAt(Index);
		return Scenario;
	}
	FScenario Scenario;
	return Scenario;
}

