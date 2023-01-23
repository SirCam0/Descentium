// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PathfindingNode.generated.h"

class AA3DNavMesh;
/**
 * UStruct template file created by Cameron.Greenway 04/11/21
 */

USTRUCT(BlueprintType)
struct FPathfindingNode
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AA3DNavMesh* Grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector GridPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Neighbors;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Score;
};