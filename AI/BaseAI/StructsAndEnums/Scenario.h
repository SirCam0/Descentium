// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Wave.h"
#include "Scenario.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FScenario
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWave> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TempCurrencyDropAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PermaCurrencyDropAmount;
};
