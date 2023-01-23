// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RoofVolume.generated.h"

UCLASS()
class DESCENTIUM_API ARoofVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoofVolume();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* CenterBox;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* LeftWall;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* RightWall;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* FrontWall;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* BackWall;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* Roof;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Bounds = FVector(100,100,100);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
