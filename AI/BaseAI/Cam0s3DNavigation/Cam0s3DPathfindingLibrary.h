// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Descentium/AI/BaseAI/NavMeshNode.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Cam0s3DPathfindingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API UCam0s3DPathfindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category=Pathfinding)
	static TArray<ANavMeshNode*> GetPath(AActor* ActorToMove, FVector TargetLocation);
	
};
