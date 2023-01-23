// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A3DNavMesh.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums/PathfindingNode.h"
#include "A3DNavMeshManager.generated.h"

class ANavMeshNode;
UCLASS()
class DESCENTIUM_API AA3DNavMeshManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA3DNavMeshManager();
	
	UFUNCTION(BlueprintCallable)
	void BuildMapNavigation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*> NavMeshActors;

	UPROPERTY(VisibleAnywhere)
	TArray<AA3DNavMesh*> NavMeshes;

	UFUNCTION(BlueprintCallable)
	void ScoreLocations();
	double ScoreSingleLocation(FVector Location) const;
	void AddNode(FPathfindingNode Node);
	
	void GetAllNodes();
	TArray<AActor*> NodesTemp;
	TArray<ANavMeshNode*> Nodes;

	FVector PreviousPlayerLocation;

	ACharacter* Player;

	UPROPERTY(EditAnywhere)
	float ScoreInterval = 5;

	FTimerHandle ScoreTimerHandle;

};
