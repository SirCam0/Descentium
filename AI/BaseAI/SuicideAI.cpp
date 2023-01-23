// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicideAI.h"

#include "ArtificialIntelligenceManager.h"
#include "NavMeshNode.h"
#include "NiagaraFunctionLibrary.h"
#include "SpawnDoorsManager.h"
#include "SuicideAISplinePath.h"
#include "SuicideSpawnerAI.h"
#include "A3DNavMeshManager.h"
//#include "Cam0s3DNavigation/Cam0s3DPathfindingLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASuicideAI::ASuicideAI()
{
	
}

void ASuicideAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	this->DeltaTime = DeltaSeconds;
	if(Player->IsValidLowLevelFast())
	{
		SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(this->GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Player->GetActorLocation()), DeltaTime, RotationSpeed));
	}
}

void ASuicideAI::Death(bool CritDeath)
{
	NavSpline->Destroy();
	RemoveFromSpawner();
	/**
	if(Spawner->IsValidLowLevelFast())
	{
		Spawner->EnemyKilled(this);
	}
	*/
	Super::Death(CritDeath);
}

void ASuicideAI::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(LifetimeTimer, this, &ASuicideAI::StartExplode, Lifetime);
	NavSys = Cast<AA3DNavMeshManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AA3DNavMeshManager::StaticClass()));
	Player = UGameplayStatics::GetPlayerCharacter(this,0);
	FActorSpawnParameters SpawnParams;
	NavSpline = GetWorld()->SpawnActor<ASuicideAISplinePath>(ASuicideAISplinePath::StaticClass(), FVector(0), FRotator(0), SpawnParams);
	StartMovement();
}

void ASuicideAI::BeginMovement()
{
	if(Player->IsValidLowLevelFast())
	{
		bFirst = true;
		JoinQueue();
	}
}

void ASuicideAI::JoinQueue()
{
	if(AITokenManager->IsValidLowLevelFast())
	{
		AITokenManager->AddToPathfindingQueue(this);
	}
}

void ASuicideAI::ChoosePath()
{
	ChoosePathBlueprint();
	/**
	if(CurrentPathNodes.Num() <= 0)
	{
		if(WaveManager->IsValidLowLevelFast() && this->IsValidLowLevelFast())
		{
			if(WaveManager->AllNavNodes.Num() != 0)
			{
				float ShortestDistanceSoFar = 9999999;
				for (ANavMeshNode* Node : WaveManager->AllNavNodes)
				{
					const float CurrentDistance = FVector::Distance(Node->Location, this->GetActorLocation());
					if(CurrentDistance < ShortestDistanceSoFar)
					{
						ShortestDistanceSoFar = CurrentDistance;
						ClosestNode = Node;
					}
				}
				if(ClosestNode->IsValidLowLevelFast())
				{
					if(UsedNodes.Num() > 5)
					{
						UsedNodes.RemoveAt(0);
					}
					UsedNodes.Add(ClosestNode);
					CurrentPathNodes.Add(ClosestNode);
				}
			}
		}
	}
	else
	{
		ANavMeshNode* NextNode = CurrentPathNodes[CurrentPathNodes.Num()-1]->CalculateBestNextNode(UsedNodes);
		if(UsedNodes.Num() > 5)
		{
			UsedNodes.RemoveAt(0);
		}
		UsedNodes.Add(ClosestNode);
		CurrentPathNodes.Add(NextNode);
	}
	//UCam0s3DPathfindingLibrary::GetPath(this,GetActorLocation());
	NavSpline->Spline->ClearSplinePoints();
	if(CurrentPathNodes.Num() != 0 && NavSpline->IsValidLowLevelFast())
	{
		for(const ANavMeshNode* node: CurrentPathNodes)
		{
			NavSpline->Spline->AddSplineWorldPoint(node->Location);
		} 
	}
	FollowCurrentPath();
	*/
}

void ASuicideAI::NextNodeLoop(ANavMeshNode* PreviousNode)
{
	ANavMeshNode* NextNode = PreviousNode->CalculateBestNextNode(CurrentPathNodes);
	if(NextNode != nullptr)
	{
		//UKismetSystemLibrary::DrawDebugPoint(this, NextNode->Location, 30, FColor::Red, PathUpdateInterval);
		CurrentPathNodes.Add(NextNode);
		CurrenPathVectors.Add(NextNode->Location);
		if(!(FVector::Distance(NextNode->Location, Player->GetActorLocation()) < (NextNode->Grid->Resolution*2)))
		{
			if(LoopNum <= 6)
			{
				LoopNum++;
				NextNodeLoop(NextNode);
			}
		}
	} 
}

void ASuicideAI::FollowCurrentPath()
{
	GetWorld()->GetTimerManager().SetTimer(PathFollowTimer, this, &ASuicideAI::FollowCurrentPathInterval, 0.01, true);
}

void ASuicideAI::FollowCurrentPathInterval()
{
	if(NavSpline->IsValidLowLevelFast())
	{
		if(NavSpline->Spline->GetNumberOfSplinePoints() > 1)
		{
			if(DistanceAlongSpline >= NavSpline->Spline->GetDistanceAlongSplineAtSplinePoint(NavSpline->Spline->GetNumberOfSplinePoints()-2))
			{
				Alpha = 0;
					JoinQueue();
			}
		}
		else if (DistanceAlongSpline >= NavSpline->Spline->GetSplineLength())
		{
			Alpha = 0;
			JoinQueue();
		}
		if(CurrentPathNodes.Num() != 0)
		{
			StartExplodeCheck();
			/**
			if(CurrentPathNodes[CurrentPathNodes.Num()-1]->Grid->IsValidLowLevelFast())
			{
				if(CurrentPathNodes[CurrentPathNodes.Num()-1]->Grid->Resolution*2 > FVector::Distance(this->GetActorLocation(), Player->GetActorLocation()))
				{
					StartExplode();
				}
			}
			*/
		}
		else if (FVector::Distance(this->GetActorLocation(), Player->GetActorLocation()) <= 200)
		{
			StartExplode();
		}
		if(Alpha > 1)
		{
			DistanceAlongSpline+=MovementSpeed;
			Alpha = 0;
		}
		if(bMove)
		{
			Alpha+=0.1;
		}
		FVector OldLocation = NavSpline->Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline-MovementSpeed, ESplineCoordinateSpace::World);
		FVector NewTargetLocation = NavSpline->Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
		FVector NewLocation = UKismetMathLibrary::VLerp(OldLocation,NewTargetLocation,Alpha);
		FHitResult* HitResult = new FHitResult;
		this->SetActorLocation(NewLocation,true, HitResult);
		/* check if the movement has worked so that if it is stuck we dont increase
		the distance along spline so that if it becomes free it will teleport */
		if(HitResult->bBlockingHit)
		{
			bMove = false;
		}
		else
		{
			bMove = true;
		}
	}
}
 
void ASuicideAI::StartExplode()
{
	if(ChargeExplodeAnim->IsValidLowLevelFast())
	{
		this->GetMesh()->GetAnimInstance()->Montage_Play(ChargeExplodeAnim);
	}
	else
	{
		FinishExplode();
	}
}

void ASuicideAI::FinishExplode()
{
	DamageSphereTrace();
	if(ExplodeVFX->IsValidLowLevelFast() && !Dead)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplodeVFX, this->GetActorLocation(), this->GetActorRotation(), FVector(1));
	}
	//if(AcidPoolProjectileBlueprint->IsValidLowLevelFast())
	//{
	//	FActorSpawnParameters SpawnParams;
	//	GetWorld()->SpawnActor<AActor>(AcidPoolProjectileBlueprint, this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	//}
	Death(false);
}

