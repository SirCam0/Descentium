// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
//#include "EnemySpawnArea.h"
#include "NavMeshNode.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums/Scenario.h"
#include "StructsAndEnums/Stage.h"
#include "SpawnDoorsManager.generated.h"

class AEnemySpawnArea;
UCLASS()
class DESCENTIUM_API ASpawnDoorsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnDoorsManager();

	int CurrentWave = 0;

	UPROPERTY(BlueprintReadWrite);
	TArray<ABaseAI*> AliveEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	TArray<FTransform> OutsideDoorEnemyLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget = true))
	TArray<FTransform> UsedLocationsThisWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NextWaveHierarchyThreshhold = 5;
	
	TArray<FTransform> UsedLocations;

	UPROPERTY(VisibleAnywhere)
	FScenario Scenario;

	UFUNCTION(BlueprintCallable)
	void AddHighlightToAllEnemeies();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool Highlighting = false;
	
	UFUNCTION(BlueprintCallable)
	void RemoveHighlightFromAllEnemeies();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* RangedEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* SimulEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* SkremlinEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* MeleeEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* OdiumCirumEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* SuicideEnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	UClass* SuicideSpawnerClass;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProjectile(FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnVelocity, FVector TargetLocation);

	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	FTimerHandle InitialDelayHandle;
	float InitialDelay = 2.f;
	void AfterDelay();

	float TempCurrencyPerEnemy = 0;

	float PermaCurrencyPerEnemy = 0;

	FTimerHandle HighlightAfterTime;

	bool HighlightToggle = false;
	void ToggleHighlight();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartRoom();
	
	void SpawnNextWave();
	void EnemyDied(ABaseAI* Enemy);
	void UpdateEnemiesLeft(int& EnemiesLeftPtr, int& TotalScorePtr);
	void UpdateEnemiesLeft();
	void UpdateEnemiesLeftOnInterval();
	void RoomCleared();

	UFUNCTION(BlueprintImplementableEvent)
	AEnemySpawnArea* PickDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void PickLocation(FTransform& NonTracedLocation, FTransform& TracedLocation, ANonDoorSpawnLocation* &NonDoorSpawnLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void OpenPortal();

	UFUNCTION(BlueprintImplementableEvent)
	void ClearUsedLocations();

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> AllNavNodesActor;
	UPROPERTY(BlueprintReadWrite)
	TArray<ANavMeshNode*> AllNavNodes;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEnemiesLeftUI();

	UFUNCTION(BlueprintImplementableEvent)
	void HideEnemiesLeftUI();

	UFUNCTION(BlueprintImplementableEvent)
	void SetEnemiesLeftUI(int num);

	FTimerHandle CheckEnemiesLeftTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<ANonDoorSpawnLocation*> AvailableNonDoorSpawnLocations;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<Stage> StageNumber;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeMusicStartOfWave();
};
