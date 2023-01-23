// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "Engine/DataTable.h"
#include "StructsAndEnums/EnemyValueStructs/MeleeAIValues.h"
#include "MeleeAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AMeleeAI : public ABaseAI
{
	GENERATED_BODY()

	AMeleeAI();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(BlueprintReadWrite);
	FMeleeAIValues Data;
	
};
