// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "StructsAndEnums/EnemyValueStructs/RangedAIValues.h"
#include "RangedAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API ARangedAI : public ABaseAI
{
	GENERATED_BODY()

	ARangedAI();

	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* ChargeShotAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ChargeShotVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AccuracyDistanceRangeMax = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;

	UFUNCTION(BlueprintCallable)
	void PlayAttackAnim();

	UFUNCTION(BlueprintCallable)
	void FireBullet();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProjectile(FVector SpawnLocation, FRotator SpawnRotation, FVector SpawnVelocity, FVector TargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AccuracyDistributionCurve;

	FVector PlayerCameraOffset = FVector(0.f, 0.f, 0.f);

	UPROPERTY(BlueprintReadWrite);
	FRangedAIValues Data;
	
};
