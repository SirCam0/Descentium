// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "NavMeshNode.h"
#include "OdiumCirrumAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AOdiumCirrumAI : public ABaseAI
{
	GENERATED_BODY()
	
	AOdiumCirrumAI();

	virtual AOdiumCirrumAI* GetOdiumCirrumAIREF_Implementation() override;

	virtual void BeginPlay() override;

	ANavMeshNode* NavNode;

	virtual void Death(bool CritDeath) override;

	virtual void Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit) override;
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float OuterShellDamageMultiplier = 0.1;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ClosePortal();

};
