// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "SuicideAI.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums/AITokens.h"
#include "StructsAndEnums/TokenManagerScoreHelper.h"
#include "StructsAndEnums/TokenTypeEnum.h"
#include "ArtificialIntelligenceManager.generated.h"

UCLASS()
class DESCENTIUM_API AArtificialIntelligenceManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArtificialIntelligenceManager();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FAITokens AttackTokens;

	UPROPERTY(VisibleAnywhere)
	TArray<TEnumAsByte<TokenTypeEnum>> AvailableTokens;

	TArray<ASuicideAI*> PathFindingQueue;
	float PathfindingQueueIntervalTime = 0.1;
	FTimerHandle PathfindingQueueHandle;
	bool Pathfinding;
	
	UFUNCTION(BlueprintCallable)
	void TakeTokenOverride(TEnumAsByte<TokenTypeEnum> TokenType);

	UFUNCTION(BlueprintCallable)
	void ReturnToken(TEnumAsByte<TokenTypeEnum> TokenType);
	void swap(FTokenManagerScoreHelper* a, FTokenManagerScoreHelper* b);

	UFUNCTION(BlueprintCallable)
	void GetAllEnemies();

	TArray<ABaseAI*> AllEnemies;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector PredictedPlayerLocation;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector PredictedPlayerVelocity;

	ACharacter* PlayerCharacter;

	void printScores(TArray<FTokenManagerScoreHelper> Array, int size);

	FTimerHandle ProjectileReturnBufferTimerHandle;

	FTimerHandle MeleeReturnBufferTimerHandle;

	FTimerHandle AssignTokensLoopHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TokenTimeoutTime = 5.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void StartPathfindingQueue();
	void PathfindingQueueInterval();
	void GetClosestNodeToPlayerloop();
	void AssignTokensLoop();

	void AssignProjectileTokens();

	void AssignMeleeTokens();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddToPathfindingQueue(ASuicideAI* SuicideAI);
	FVector GetPredictedPlayerVelocity();
	FVector GetPredictedPlayerLocation();
	FVector PredictPlayerLocation(float DeltaTime);
};
