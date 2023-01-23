// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBossRedirectSpline.h"


// Sets default values
AWormBossRedirectSpline::AWormBossRedirectSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	Rail = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Rail->SetupAttachment(RootComponent);

	StartPoint = CreateDefaultSubobject<ANavMeshNode>(TEXT("StartPoint"));
	EndPoint = CreateDefaultSubobject<ANavMeshNode>(TEXT("EndPoint"));
}

// Called when the game starts or when spawned
void AWormBossRedirectSpline::BeginPlay()
{
	Super::BeginPlay();
	StartPoint->Location = Rail->GetWorldLocationAtDistanceAlongSpline(0);
	EndPoint->Location = Rail->GetWorldLocationAtDistanceAlongSpline(Rail->GetSplineLength());
}

// Called every frame
void AWormBossRedirectSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

