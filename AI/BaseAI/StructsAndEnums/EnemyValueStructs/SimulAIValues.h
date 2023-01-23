// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "SimulAIValues.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FSimulAIValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ChargeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeKnockback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeStunDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SlamDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlamKnockback;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SlamRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeHooked;
	
};
