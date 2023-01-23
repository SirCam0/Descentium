// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicideAISplinePath.h"

// Sets default values
ASuicideAISplinePath::ASuicideAISplinePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);
	Spline->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ASuicideAISplinePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuicideAISplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

