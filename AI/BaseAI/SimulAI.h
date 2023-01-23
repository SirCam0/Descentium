// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "Components/BoxComponent.h"
#include "StructsAndEnums/EnemyValueStructs/SimulAIValues.h"
#include "SimulAI.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API ASimulAI : public ABaseAI
{
	GENERATED_BODY()

	ASimulAI* GetSimulAIREF_Implementation() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void ChargeWedgeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void ChargeWedgeOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ASimulAI();

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool Charging = false;

	UPROPERTY(BlueprintReadWrite)
	bool HitPlayerDoOnce = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool ChargeAvaiable = true;

	UPROPERTY(BlueprintReadWrite)
	FSimulAIValues Values;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void PlayerHit();

	UFUNCTION(BlueprintImplementableEvent)
	void EndCharge();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ChargeWedge;
};
