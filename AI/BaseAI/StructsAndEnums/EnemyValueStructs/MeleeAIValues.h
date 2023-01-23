// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "MeleeAIValues.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FMeleeAIValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShieldHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SingleSwipeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DoubleSwipeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeHooked;
};
