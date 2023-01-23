// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Enemy.h"
#include "Wave.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemy> Enemies;
};
