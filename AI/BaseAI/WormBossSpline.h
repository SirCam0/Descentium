// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "WormBossSpline.generated.h"

UCLASS()
class DESCENTIUM_API AWormBossSpline : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;


public:
	// Sets default values for this actor's properties
	AWormBossSpline();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USplineComponent* Rail;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
