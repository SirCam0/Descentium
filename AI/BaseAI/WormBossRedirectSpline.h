// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavMeshNode.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "WormBossRedirectSpline.generated.h"

UCLASS()
class DESCENTIUM_API AWormBossRedirectSpline : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USplineComponent* Rail;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ANavMeshNode* StartPoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ANavMeshNode* EndPoint;
	
	
	// Sets default values for this actor's properties
	AWormBossRedirectSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
