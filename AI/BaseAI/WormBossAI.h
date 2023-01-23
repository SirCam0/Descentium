// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "WormBossSpline.h"
#include "WormBossAI.generated.h"

class ANavMeshNode;
class APortal;
/**
 * 
 */
UCLASS()
class DESCENTIUM_API AWormBossAI : public ABaseAI
{
	GENERATED_BODY()

	AWormBossAI();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelay = 1;
	FTimerHandle SpawnDelayTimer;
	UFUNCTION(BlueprintCallable)
	void AfterSpawnDelay();

	UFUNCTION(BlueprintCallable)
	void SetMoveToLocation(FVector location);
	UFUNCTION(BlueprintCallable)
	void Grow(int Amount);
	UFUNCTION(BlueprintImplementableEvent)
	void ChoosePathBP(FVector TargetLocation);

	UFUNCTION()
	void MoveAlongSplineInterval();
	FTimerHandle MovementTimer;

	UPROPERTY(BlueprintReadWrite)
	AWormBossSpline* Spline;

	APortal* StartPortal;
	bool DoOnce = false;
	bool DoOnce2 = false;
	APortal* EndPortal;

	UPROPERTY(BlueprintReadWrite)
	TArray<ANavMeshNode*> NavNodes;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> BodyParts;

	UStaticMeshComponent* TailPart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Head;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Body;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Tail;

	UFUNCTION(BlueprintCallable)
	void TeleportToNewLocation(FVector location, FRotator rotation);
	bool teleporting = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool moving = true;

	UFUNCTION(BlueprintCallable)
	void PickNewMoveToLocation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Sections = 15;

	UPROPERTY(VisibleAnywhere)
	int CurrentSections = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectionSize = 75;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentDistanceAlongSpline = 0;
	float MovementSpeed = 3;
};
