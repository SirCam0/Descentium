// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A3DNavMesh.h"
#include "NavMeshNodeInterface.h"
#include "GameFramework/Actor.h"
#include "NavMeshNode.generated.h"

UCLASS()
class DESCENTIUM_API ANavMeshNode : public AActor, public INavMeshNodeInterface
{
	GENERATED_BODY()

	virtual ANavMeshNode* GetNavMeshNodeREF_Implementation() override;
	
public:	
	// Sets default values for this actor's properties
	ANavMeshNode();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta = (ExposeOnSpawn="true", MakeEditWidget = true))
	FVector Location;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<ANavMeshNode*> Neighbours;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta = (ExposeOnSpawn="true"))
	AA3DNavMesh* Grid;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta = (ExposeOnSpawn="true"))
	FVector GridPosition;

	ACharacter* Player;
	
	UFUNCTION(BlueprintCallable)
	void GetNeighbours();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	float GetHeuristic();

	float GetHeuristicCustomLoc(FVector location);

	UFUNCTION(BlueprintCallable)
	ANavMeshNode* CalculateBestNextNode(TArray<ANavMeshNode*> PreviousNodes);

	UFUNCTION(BlueprintCallable)
	ANavMeshNode* CalculateBestNextNodeCustom(TArray<ANavMeshNode*> PreviousNodes, FVector loc);
};
