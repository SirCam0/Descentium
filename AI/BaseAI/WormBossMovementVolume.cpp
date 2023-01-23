// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBossMovementVolume.h"


// Sets default values
AWormBossMovementVolume::AWormBossMovementVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AWormBossMovementVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWormBossMovementVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

