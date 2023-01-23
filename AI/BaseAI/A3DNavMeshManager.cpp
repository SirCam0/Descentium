// Fill out your copyright notice in the Description page of Project Settings.


#include "A3DNavMeshManager.h"

#include "NavMeshNode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AA3DNavMeshManager::AA3DNavMeshManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AA3DNavMeshManager::BuildMapNavigation()
{
	NavMeshActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA3DNavMesh::StaticClass(), NavMeshActors);
	NavMeshes.Empty();
	for (int i = 0; i <= NavMeshActors.Num(); i++)
	{
		if(NavMeshActors.IsValidIndex(i))
		{
			NavMeshes.Add(Cast<AA3DNavMesh>(NavMeshActors[i]));
		}
	}
	for(AA3DNavMesh* NavMesh : NavMeshes)
	{
		NavMesh->BuildNavigation();
	}
	GetAllNodes();
	for (ANavMeshNode* Node : Nodes)
	{
		Node->GetNeighbours();
	}
}

// Called when the game starts or when spawned
void AA3DNavMeshManager::BeginPlay()
{
	Super::BeginPlay();
	NavMeshActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA3DNavMesh::StaticClass(), NavMeshActors);
	NavMeshes.Empty();
	for (int i = 0; i <= NavMeshActors.Num(); i++)
	{
		if(NavMeshActors.IsValidIndex(i))
		{
			NavMeshes.Add(Cast<AA3DNavMesh>(NavMeshActors[i]));
		}
	}
	Player = UGameplayStatics::GetPlayerCharacter(this,0);
	GetWorld()->GetTimerManager().SetTimer(ScoreTimerHandle, this, &AA3DNavMeshManager::ScoreLocations, ScoreInterval, true, 1);
}

void AA3DNavMeshManager::GetAllNodes()
{
	NodesTemp.Empty();
	Nodes.Empty();
	UGameplayStatics::GetAllActorsOfClass(this, ANavMeshNode::StaticClass(), NodesTemp);
	for (AActor* Node : NodesTemp)
	{
		if(Node->Implements<UNavMeshNodeInterface>())
		{
			Nodes.Add(INavMeshNodeInterface::Execute_GetNavMeshNodeREF(Node));
		}
	}
}

// Called every frame
void AA3DNavMeshManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AA3DNavMeshManager::ScoreLocations()
{
	if(Player->IsValidLowLevelFast())
	{
		if(Player->GetActorLocation() != PreviousPlayerLocation)
		{
			PreviousPlayerLocation = Player->GetActorLocation();
		}
	}
}

double AA3DNavMeshManager::ScoreSingleLocation(FVector Location) const
{
	return FVector::Distance(Location, Player->GetActorLocation());
}
void AA3DNavMeshManager::AddNode(FPathfindingNode Node)
{
	
}

