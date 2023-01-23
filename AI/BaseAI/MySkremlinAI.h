// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "MySkremlinAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AMySkremlinAI : public ABaseAI
{
	GENERATED_BODY()

	AMySkremlinAI* GetSkremlinAIREF_Implementation() override;

	virtual void BeginPlay() override;

	virtual void Death(bool CritDeath) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void PlayAttackAnim();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Attacking = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Swinging = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AmountOfCoinsToSteal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoinsPerSecondLost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageAmount;

	AArtificialIntelligenceManager* AIManager;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int CoinsHeld = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void ReturnCoins(int Amount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StealCoins();

	UFUNCTION(BlueprintCallable)
	void ResetSwinging();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* AttackAnim;
};
