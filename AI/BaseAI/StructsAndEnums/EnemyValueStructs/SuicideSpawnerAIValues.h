// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "SuicideSpawnerAIValues.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FSuicideSpawnerAIValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSuicideEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GasCloudDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeHooked;
};
