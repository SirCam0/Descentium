// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HitReactionThresholds.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FHitReactionThresholds
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Twitch;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Falter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stagger;
};
