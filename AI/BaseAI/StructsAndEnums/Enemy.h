// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnemyType.h"
#include "Enemy.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EnemyType> Enemy = EnemyType::Ranged;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number = 0;

	
};
