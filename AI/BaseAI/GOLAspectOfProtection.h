// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOLBaseAI.h"
#include "GOLAspectOfProtection.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AGOLAspectOfProtection : public AGOLBaseAI
{
	GENERATED_BODY()

	virtual void Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit) override;

	bool DoOnce = false;

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void HalfHealth();
};
