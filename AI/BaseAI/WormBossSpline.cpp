// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBossSpline.h"


// Sets default values
AWormBossSpline::AWormBossSpline()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Rail = CreateDefaultSubobject<USplineComponent>(TEXT("Rail"));
	Rail->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWormBossSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWormBossSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

