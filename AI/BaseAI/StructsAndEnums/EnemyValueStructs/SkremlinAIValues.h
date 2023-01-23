// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "SkremlinAIValues.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FSkremlinAIValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int	ShieldHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CoinsToSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoinsPerSecondLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeHooked;
};
