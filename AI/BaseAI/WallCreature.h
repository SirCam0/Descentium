// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI.h"
#include "Components/TimelineComponent.h"
#include "WallCreature.generated.h"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API AWallCreature : public ABaseAI
{
	GENERATED_BODY()

	AWallCreature();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex);

	bool PlayerInside;

	////Scale timeline
	class UTimelineComponent* ScaleTimeline;
	
	UFUNCTION()
	void ScaleFloatReturn(float value);
	FOnTimelineFloat ScaleUpdateFunction{};

	UFUNCTION()
	void ScaleFinished();
	FOnTimelineEvent ScaleFinishedFunction{};

	UPROPERTY(EditAnywhere, Category = "Scale Timeline")
	class UCurveFloat* ScaleCurve;
	////

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionSphere;
};
