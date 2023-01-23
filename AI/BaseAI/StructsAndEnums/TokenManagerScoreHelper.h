// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Descentium/AI/BaseAI/BaseAI.h"
#include "TokenManagerScoreHelper.generated.h"

/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FTokenManagerScoreHelper
{
	GENERATED_BODY()

	UPROPERTY()
	ABaseAI* Enemy;

	UPROPERTY()
	float Score;
	
	//FTokenManagerScoreHelper();

	//FTokenManagerScoreHelper(ABaseAI* EnemyRef, float InitialScore)
	//{
	//	this->Enemy = EnemyRef;
	//	this->Score = InitialScore;
	//}
};
