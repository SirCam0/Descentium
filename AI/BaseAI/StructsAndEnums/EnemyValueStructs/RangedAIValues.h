// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "RangedAIValues.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FRangedAIValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ShieldHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed_Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSlowAmountOnHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AccuracyCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeHooked;
};
