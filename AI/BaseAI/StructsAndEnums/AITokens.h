// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AITokens.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FAITokens
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ProjectileTokens = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MeleeTokens = 0;
};
