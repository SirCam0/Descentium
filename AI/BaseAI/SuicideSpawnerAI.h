// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "NavMeshNode.h"
#include "SuicideSpawnerAI.generated.h"
/**
 * 
 */
UCLASS()
class DESCENTIUM_API ASuicideSpawnerAI : public ABaseAI
{
	GENERATED_BODY()

	ASuicideSpawnerAI* GetSpawnerAIREF_Implementation() override;
	
	USphereComponent* ProximityCollisionSphere;

	ANavMeshNode* ExitNode;

	ASuicideSpawnerAI();

	virtual void BeginPlay() override;
	void SpawnEnemyLoop();

public:

	FTimerHandle SpawnEnemyLoopTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* SpawnAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ProximityVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* SpurtVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* SuicideEnemy;

	TArray<ABaseAI*> SpawnedEnemies;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool Spawning = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxSuicideEnemies = 5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SpawnInterval = 5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CollisionSphereRadius = 350;

	void PlaySpawnAnimation();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent)
	void DamagePlayer();

	UFUNCTION(BlueprintCallable)
	void EnemyKilled(ABaseAI* KilledEnemy);

	UFUNCTION()
	void ProximityBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
