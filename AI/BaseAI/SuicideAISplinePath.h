// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "SuicideAISplinePath.generated.h"

UCLASS()
class DESCENTIUM_API ASuicideAISplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuicideAISplinePath();

	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
