// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A3DNavMeshManager.h"
#include "BaseAI.h"
#include "SuicideAISplinePath.h"
#include "SuicideAI.generated.h"

class ASuicideSpawnerAI;
/**
 * 
 */
UCLASS()
class DESCENTIUM_API ASuicideAI : public ABaseAI
{
	GENERATED_BODY()

	virtual void Death(bool CritDeath) override;

	virtual void BeginPlay() override;

	float DistanceAlongSpline = 0;
	float Alpha = 0;
	
	void NextNodeLoop(ANavMeshNode* PreviousNode);

	UFUNCTION(BlueprintCallable)
	void FollowCurrentPath();
	void FollowCurrentPathInterval();

	UFUNCTION(BlueprintCallable)
	void StartExplode();

	UFUNCTION(BlueprintCallable)
	void FinishExplode();

	ASuicideAI();

	FTimerHandle PathUpdateTimer;

	FTimerHandle LifetimeTimer;

	FTimerHandle PathFollowTimer;
	float PathFollowInterval = 0.01f;

	float DeltaTime;
	
	float MovementSpeed = 50;

	float RotationSpeed = 300;

	int CurrentNode = 0;

	float RequiredDistance = 95;

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void RemoveFromSpawner();

	UPROPERTY(BlueprintReadWrite)
	ASuicideAISplinePath* NavSpline;

	UPROPERTY(BlueprintReadWrite)
	ANavMeshNode* ClosestNode = nullptr;

	bool bFirst = true;
	
	bool bMove = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lifetime = 15;

	void ChoosePath();

	UFUNCTION(BlueprintImplementableEvent)
	void ChoosePathBlueprint();
	
	int LoopNum = 0;
	
	UFUNCTION(BlueprintCallable)
	void BeginMovement();
	void JoinQueue();

	UFUNCTION(BlueprintImplementableEvent)
	void StartMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageAmount = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* ChargeExplodeAnim;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* AcidPoolProjectileBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ExplodeVFX;


	UPROPERTY(VisibleAnywhere)
	AA3DNavMeshManager* NavSys;

	UPROPERTY(BlueprintReadWrite)
	ASuicideSpawnerAI* Spawner;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite)
	AActor* Player;

	UPROPERTY(BlueprintReadWrite)
	ANavMeshNode* FirstNode;
	UPROPERTY(BlueprintReadWrite)
	TArray<ANavMeshNode*> CurrentPathNodes;
	UPROPERTY(BlueprintReadWrite)
	TArray<ANavMeshNode*> UsedNodes;
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> CurrenPathVectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PathUpdateInterval = 5; //longer = better performance, Shorter = More Accurate

	float TargetDistance = 100;

	UFUNCTION(BlueprintImplementableEvent)
	void StartExplodeCheck();

	UFUNCTION(BlueprintImplementableEvent)
	void DamageSphereTrace();
};
