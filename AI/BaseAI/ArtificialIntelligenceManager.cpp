// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtificialIntelligenceManager.h"

#include "BaseAI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "StructsAndEnums/TokenManagerScoreHelper.h"

// Sets default values
AArtificialIntelligenceManager::AArtificialIntelligenceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AArtificialIntelligenceManager::BeginPlay()
{
	Super::BeginPlay();
	for (int i = AttackTokens.MeleeTokens; i > 0; i--)
    {
        AvailableTokens.Add(TokenTypeEnum::Melee);
    }
    for (int i = AttackTokens.ProjectileTokens; i > 0; i--)
    {
    	AvailableTokens.Add(TokenTypeEnum::Projectile);
    }
	//AssignProjectileTokens();
	//AssignMeleeTokens();
	GetWorld()->GetTimerManager().SetTimer(AssignTokensLoopHandle, this, &AArtificialIntelligenceManager::AssignTokensLoop,1,true);
}

void AArtificialIntelligenceManager::AddToPathfindingQueue(ASuicideAI* SuicideAI)
{
	PathFindingQueue.AddUnique(SuicideAI);
	if(!Pathfinding)
	{
		Pathfinding = true;
		StartPathfindingQueue();
	}
}

void AArtificialIntelligenceManager::StartPathfindingQueue()
{
	GetWorld()->GetTimerManager().SetTimer(PathfindingQueueHandle, this, &AArtificialIntelligenceManager::PathfindingQueueInterval, PathfindingQueueIntervalTime, true);
}

void AArtificialIntelligenceManager::PathfindingQueueInterval()
{
	if(PathFindingQueue.Num() != 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Pathfinding queue num != 0"));
		if (PathFindingQueue[0]->IsValidLowLevelFast() && PathFindingQueue.Num() != 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Pathfinding queue[0] valid"));
			PathFindingQueue[0]->ChoosePath();
			PathFindingQueue.RemoveAt(0);
		}
	}
	else
	{
		Pathfinding = false;
		PathfindingQueueHandle.Invalidate();
	}
}

void AArtificialIntelligenceManager::AssignTokensLoop()
{
	if(AvailableTokens.Contains(TokenTypeEnum::Projectile))
	{
		AssignProjectileTokens();
	}
	if(AvailableTokens.Contains(TokenTypeEnum::Melee))
	{
		AssignMeleeTokens();
	}
}

void AArtificialIntelligenceManager::GetAllEnemies()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseAI::StaticClass(), Actors);
	AllEnemies.Empty();
	for (const auto Actor : Actors)
	{
		AllEnemies.Add(Cast<ABaseAI>(Actor));
	}
}

void AArtificialIntelligenceManager::TakeTokenOverride(TEnumAsByte<TokenTypeEnum> TokenType)
{
	
}

void AArtificialIntelligenceManager::ReturnToken(TEnumAsByte<TokenTypeEnum> TokenType)
{
	AvailableTokens.Add(TokenType);
	if(TokenType == TokenTypeEnum::Projectile)
	{
		//GetWorld()->GetTimerManager().SetTimer(ProjectileReturnBufferTimerHandle, this, &AArtificialIntelligenceManager::AssignProjectileTokens, 0.5f, false);
	}
	if(TokenType == TokenTypeEnum::Melee)
	{
		//GetWorld()->GetTimerManager().SetTimer(MeleeReturnBufferTimerHandle, this, &AArtificialIntelligenceManager::AssignMeleeTokens, 0.5f, false);
	}
}

void AArtificialIntelligenceManager::AssignProjectileTokens()
{
	GetAllEnemies();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AssigningTokens")));
	const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	TArray<FTokenManagerScoreHelper> Scores;
	for (auto Enemy : AllEnemies)
	{
		if(Enemy->UsedTokenTypes.Contains(TokenTypeEnum::Projectile))
		{
			FTokenManagerScoreHelper ScoreStruct;
			ScoreStruct.Enemy = Enemy;
			FHitResult TraceHitResult;
			FCollisionQueryParams TraceParams(FName(TEXT("TraceVisibility")),false,this);
			if(GetWorld()->LineTraceSingleByChannel(TraceHitResult, Enemy->GetActorLocation(), Player->GetActorLocation(), ECC_Visibility, TraceParams))
			{
				ScoreStruct.Score = 0;
			}
			else if (Enemy->CurrentHeldTokens.Contains(TokenTypeEnum::Projectile))
			{
				ScoreStruct.Score = 0;
			}
			else if (!Enemy->AwaitingToken)
			{
				ScoreStruct.Score = 0;
			}
			else
			{
				const float Distance = (Enemy->GetActorLocation() - Player->GetActorLocation()).Size();
				float DistanceScore = FMath::GetMappedRangeValueClamped(FVector2D(0,150),FVector2D(1.5,0),Distance/100);
				float DotProductScore = FMath::GetMappedRangeValueClamped(FVector2D(-1,1),
					FVector2D(0,1), FVector::DotProduct(
						Player->GetActorForwardVector(),
					UKismetMathLibrary::GetForwardVector(
						UKismetMathLibrary::FindLookAtRotation(
							Player->GetActorLocation(), Enemy->GetActorLocation()))));
				ScoreStruct.Score = DistanceScore + DotProductScore;
			}
			Scores.Add(ScoreStruct);
		}
	}
	//int n = Scores.Num();
	//printScores(Scores,n);
	TArray<FTokenManagerScoreHelper> TokenAssignments;
	int32 ProjectileTokens = 0;
	for (auto Token : AvailableTokens)
	{
		if (Token == TokenTypeEnum::Projectile)
		{
			ProjectileTokens++;
		}
	}
	for (int Tokens = ProjectileTokens; Tokens > 0; Tokens--)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AssigningToken")));
		FTokenManagerScoreHelper CurrentHighest;
		CurrentHighest.Enemy = nullptr;
		CurrentHighest.Score = 0;
		int index = 0;
		int HighestIndex = -1;
		for (auto ScoreItem : Scores)
		{
			if(ScoreItem.Score != 0)
			{
				if(ScoreItem.Score > CurrentHighest.Score)
				{
					CurrentHighest = ScoreItem;
					HighestIndex = index;
				}
			}
			index++;
		}
		if(HighestIndex != -1)
		{
			Scores.RemoveAt(HighestIndex);
			TokenAssignments.Add(CurrentHighest);
		}
	}
	//int numAssigned = 0;
	for (auto Assignment : TokenAssignments)
	{
		if(Assignment.Enemy->IsValidLowLevelFast())
		{
			//numAssigned++;
			Assignment.Enemy->ReceiveToken(TokenTypeEnum::Projectile, TokenTimeoutTime);
			int TokenIndex = -1;
			int index = 0;
			for (auto Token : AvailableTokens)
			{
				if(Token==TokenTypeEnum::Projectile)
				{
					TokenIndex = index;
				}
				index++;
			}
			if(TokenIndex != -1)
			{
				this->AvailableTokens.RemoveAt(TokenIndex);
			}
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%i"), numAssigned));
}

void AArtificialIntelligenceManager::printScores(TArray<FTokenManagerScoreHelper> Array, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 55.f, FColor::Red, FString::Printf(TEXT("%f"), Array[i].Score));
	}
}

//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AssigningToken")));

void AArtificialIntelligenceManager::AssignMeleeTokens()
{
	GetAllEnemies();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("AssigningTokens")));
	const ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	TArray<FTokenManagerScoreHelper> Scores;
	for (auto Enemy : AllEnemies)
	{
		if(Enemy->UsedTokenTypes.Contains(TokenTypeEnum::Melee))
		{
			FTokenManagerScoreHelper ScoreStruct;
			ScoreStruct.Enemy = Enemy;
			FHitResult TraceHitResult;
			FCollisionQueryParams TraceParams(FName(TEXT("TraceVisibility")),false,this);
			if(GetWorld()->LineTraceSingleByChannel(TraceHitResult, Enemy->GetActorLocation(), Player->GetActorLocation(), ECC_Visibility, TraceParams))
			{
				ScoreStruct.Score = 0;
			}
			else if (Enemy->CurrentHeldTokens.Contains(TokenTypeEnum::Melee))
			{
				ScoreStruct.Score = 0;
			}
			else if (!Enemy->AwaitingToken)
			{
				ScoreStruct.Score = 0;
			}
			else
			{
				const float Distance = (Enemy->GetActorLocation() - Player->GetActorLocation()).Size();
				float DistanceScore = FMath::GetMappedRangeValueClamped(FVector2D(0,150),FVector2D(1.5,0),Distance/100);
				float DotProductScore = FMath::GetMappedRangeValueClamped(FVector2D(-1,1),
					FVector2D(0,1), FVector::DotProduct(
						Player->GetActorForwardVector(),
					UKismetMathLibrary::GetForwardVector(
						UKismetMathLibrary::FindLookAtRotation(
							Player->GetActorLocation(), Enemy->GetActorLocation()))));
				ScoreStruct.Score = DistanceScore + DotProductScore;
			}
			Scores.Add(ScoreStruct);
		}
	}
	//int n = Scores.Num();
	//printScores(Scores,n);
	TArray<FTokenManagerScoreHelper> TokenAssignments;
	int32 MeleeTokens = 0;
	for (auto Token : AvailableTokens)
	{
		if (Token == TokenTypeEnum::Melee)
		{
			MeleeTokens++;
		}
	}
	for (int Tokens = MeleeTokens; Tokens > 0; Tokens--)
	{
		FTokenManagerScoreHelper CurrentHighest;
		CurrentHighest.Enemy = nullptr;
		CurrentHighest.Score = 0;
		int index = 0;
		int HighestIndex = -1;
		for (auto ScoreItem : Scores)
		{
			if(ScoreItem.Score != 0)
			{
				if(ScoreItem.Score > CurrentHighest.Score)
				{
					CurrentHighest = ScoreItem;
					HighestIndex = index;
				}
			}
			index++;
		}
		if(HighestIndex != -1)
		{
			Scores.RemoveAt(HighestIndex);
			TokenAssignments.Add(CurrentHighest);
		}
	}
	//int numAssigned = 0;
	for (auto Assignment : TokenAssignments)
	{
		if(Assignment.Enemy->IsValidLowLevelFast())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("TokenAssigned")));
			//numAssigned++;
			Assignment.Enemy->ReceiveToken(TokenTypeEnum::Melee, TokenTimeoutTime);
			int TokenIndex = -1;
			int index = 0;
			for (auto Token : AvailableTokens)
			{
				if(Token==TokenTypeEnum::Melee)
				{
					TokenIndex = index;
				}
				index++;
			}
			if(TokenIndex != -1)
			{
				this->AvailableTokens.RemoveAt(TokenIndex);
			}
		}
	}
}

FVector AArtificialIntelligenceManager::PredictPlayerLocation(float DeltaTime)
{
	if(!(PlayerCharacter->IsValidLowLevelFast()))
	{
		PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}
	if(PlayerCharacter->IsValidLowLevelFast())
	{
		const FVector PlayerVelocity = PlayerCharacter->GetVelocity();
		const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		const FVector CurrentProjectedPath = PlayerLocation+PlayerVelocity;
		if(PredictedPlayerLocation == FVector(0))
		{
			PredictedPlayerLocation = CurrentProjectedPath;
		}
		PredictedPlayerLocation = UKismetMathLibrary::VInterpTo_Constant(PredictedPlayerLocation, CurrentProjectedPath, DeltaTime, 800.f);
		PredictedPlayerVelocity = UKismetMathLibrary::VInterpTo_Constant(PredictedPlayerVelocity, PlayerVelocity, DeltaTime, 2000.f);
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, FString::Printf(TEXT("PredictedLocation %s"), *PredictedPlayerLocation.ToString()));
		return PredictedPlayerLocation;
	}
	else
	{
		return FVector(0);
	}
}


// Called every frame
void AArtificialIntelligenceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PredictPlayerLocation(DeltaTime);
}

FVector AArtificialIntelligenceManager::GetPredictedPlayerVelocity()
{
	return this->PredictedPlayerVelocity;
}

FVector AArtificialIntelligenceManager::GetPredictedPlayerLocation()
{
	return this->PredictedPlayerLocation;
}
