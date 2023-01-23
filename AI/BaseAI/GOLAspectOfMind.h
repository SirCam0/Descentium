// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOLBaseAI.h"
#include "GOLAspectOfMind.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AGOLAspectOfMind : public AGOLBaseAI
{
	GENERATED_BODY()

	virtual void Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit) override;

public:

	UPROPERTY(BlueprintReadWrite)
	float ChargeUpDisruptionAmount = 500;

	UPROPERTY(BlueprintReadWrite)
	float CurrentChargeUpTotal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ChargeUpDamageAmount;

	UFUNCTION(BlueprintImplementableEvent)
	void StopChargeUp();

};
