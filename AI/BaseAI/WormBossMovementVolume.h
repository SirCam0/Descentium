// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WormBossMovementVolume.generated.h"

UCLASS()
class DESCENTIUM_API AWormBossMovementVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWormBossMovementVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
