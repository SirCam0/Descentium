// Fill out your copyright notice in the Description page of Project Settings.


#include "NavMeshNode.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ANavMeshNode* ANavMeshNode::GetNavMeshNodeREF_Implementation()
{
	return this;
}

// Sets default values
ANavMeshNode::ANavMeshNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void ANavMeshNode::GetNeighbours()
{
	//UE_LOG(LogTemp, Warning, TEXT("Getting Neighbors"));
	TArray<AActor*> Temp;
	UGameplayStatics::GetAllActorsOfClass(this, ANavMeshNode::StaticClass(), Temp);
	if(Temp.Num() != 0)
	{
		for (AActor* Actor : Temp)
		{
			if(Actor->IsValidLowLevelFast() && Grid->IsValidLowLevelFast())
			{
				ANavMeshNode* node = INavMeshNodeInterface::Execute_GetNavMeshNodeREF(Actor);
				float distance = FVector::Distance(node->Location,Location);
				//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("%f"), distance));
				if(Actor != this && distance < (Grid->Resolution*4))
				{
					Neighbours.Add(node);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ANavMeshNode::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
}

float ANavMeshNode::GetHeuristic()
{
	if(Player->IsValidLowLevelFast())
	{
		return FVector::Distance(this->Location, Player->GetActorLocation());
	}
	else
	{
		return 0;
	}
}

float ANavMeshNode::GetHeuristicCustomLoc(FVector location)
{
	return FVector::Distance(this->Location, location);
}

struct NodeScoreHelper
{
	ANavMeshNode* node;
	float Distance;

	NodeScoreHelper();

	NodeScoreHelper(ANavMeshNode* Node, float Score)
	{
		this->node = Node;
		this->Distance = Score;
	}
};

ANavMeshNode* ANavMeshNode::CalculateBestNextNode(TArray<ANavMeshNode*> PreviousNodes)
{
	TArray<NodeScoreHelper*> scores;
	if(Neighbours.Num() == 0)
	{
		GetNeighbours();
	}
	// for each neighbor calculate its score
	for (ANavMeshNode* Node : Neighbours)
	{
		bool used = false;
		if(Node->IsValidLowLevelFast())
		{
			for(ANavMeshNode* PrevNode: PreviousNodes)
			{
				if (PrevNode == Node)
				{
					used = true;
				}
			}
			if(!used)
			{
				NodeScoreHelper* NodeScore = new NodeScoreHelper(Node, FVector::Distance(this->Location, Node->Location));
				if(NodeScore != nullptr)
				{
					scores.Add(NodeScore);
				}
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%i"), scores.Num()));
	if(scores.Num() != 0)
	{
		ANavMeshNode* BestNode = scores[0]->node;
		NodeScoreHelper* BestScore = scores[0];
		for (NodeScoreHelper* Score : scores)
		{
			const float TotalScore = Score->Distance + Score->node->GetHeuristic();
			if(TotalScore <= BestScore->Distance + BestScore->node->GetHeuristic())
			{
				BestNode = Score->node;
				BestScore = Score;
			}
		}
		return BestNode;
	}
	else
	{
		return nullptr;
	}
}

ANavMeshNode* ANavMeshNode::CalculateBestNextNodeCustom(TArray<ANavMeshNode*> PreviousNodes, FVector loc)
{
	TArray<NodeScoreHelper*> scores;
	if(Neighbours.Num() == 0)
	{
		GetNeighbours();
	}
	// for each neighbor calculate its score
	for (ANavMeshNode* Node : Neighbours)
	{
		bool used = false;
		if(Node->IsValidLowLevelFast())
		{
			for(ANavMeshNode* PrevNode: PreviousNodes)
			{
				if (PrevNode == Node)
				{
					used = true;
				}
			}
			if(!used)
			{
				NodeScoreHelper* NodeScore = new NodeScoreHelper(Node, FVector::Distance(this->Location, Node->Location));
				if(NodeScore != nullptr)
				{
					scores.Add(NodeScore);
				}
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%i"), scores.Num()));
	if(scores.Num() != 0)
	{
		ANavMeshNode* BestNode = scores[0]->node;
		NodeScoreHelper* BestScore = scores[0];
		for (NodeScoreHelper* Score : scores)
		{
			const float TotalScore = Score->Distance + Score->node->GetHeuristicCustomLoc(loc);
			if(TotalScore <= BestScore->Distance + BestScore->node->GetHeuristicCustomLoc(loc))
			{
				BestNode = Score->node;
				BestScore = Score;
			}
		}
		return BestNode;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, FString::Printf(TEXT("Returning null")));
		return nullptr;
	}
}

