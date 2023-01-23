// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "SpawnDoorsManager.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnArea.generated.h"


UCLASS()
class DESCENTIUM_API AEnemySpawnArea : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CentrePoint;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SpawnAreaBounds;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnArea1;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnArea2;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnArea3;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Exit;

	UPROPERTY()
	float TempCurrencyPerEnemy;

	UPROPERTY()
	float PermaCurrencyPerEnemy;
	
	FVector SpawnArea1Loc;
	FVector SpawnArea2Loc;
	FVector SpawnArea3Loc;
	
	// Sets default values for this actor's properties
	AEnemySpawnArea();
	void SpawnEnemyFromQueue();
	FVector PickSpawnLocation();

	TArray<UClass*> SpawnQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> EnemiesEntered; 

	FTimerHandle SpawnEnemiesFromQueueTimerHandle;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();

	UPROPERTY(BlueprintReadWrite)
	ASpawnDoorsManager* Manager;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Zone1Empty = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Zone2Empty = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Zone3Empty = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
