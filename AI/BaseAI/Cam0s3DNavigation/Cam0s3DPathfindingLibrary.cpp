// Fill out your copyright notice in the Description page of Project Settings.


#include "Cam0s3DPathfindingLibrary.h"

#include "Kismet/GameplayStatics.h"

TArray<ANavMeshNode*> UCam0s3DPathfindingLibrary::GetPath(AActor* ActorToMove, FVector TargetLocation)
{
	TArray<ANavMeshNode*> Path;
	TArray<AActor*> AllNodes;
	UGameplayStatics::GetAllActorsOfClass(ActorToMove, ANavMeshNode::StaticClass(), AllNodes);
	return Path;
}
