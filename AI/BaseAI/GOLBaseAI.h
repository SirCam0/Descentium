// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "GOLBaseAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AGOLBaseAI : public ABaseAI
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	virtual void Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit) override;
	
	UFUNCTION(BlueprintCallable)
	void ResetShield();
	
	UFUNCTION(BlueprintCallable)
	void EnableShield();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int ShieldHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ShieldHealthMax;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool ShieldUp;
	
};
