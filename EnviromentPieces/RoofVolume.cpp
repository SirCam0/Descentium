// Fill out your copyright notice in the Description page of Project Settings.


#include "RoofVolume.h"

// Sets default values
ARoofVolume::ARoofVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CenterBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CenterBox"));
	CenterBox->SetupAttachment(RootComponent);
	CenterBox->SetCollisionProfileName("OverlapOnlyPlayer");

	LeftWall = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWall"));
	LeftWall->SetupAttachment(RootComponent);
	LeftWall->SetCollisionProfileName("BlockOnlyPlayer");

	RightWall = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWall"));
	RightWall->SetupAttachment(RootComponent);
	RightWall->SetCollisionProfileName("BlockOnlyPlayer");

	FrontWall = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontWall"));
	FrontWall->SetupAttachment(RootComponent);
	FrontWall->SetCollisionProfileName("BlockOnlyPlayer");

	BackWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BackWall"));
	BackWall->SetupAttachment(RootComponent);
	BackWall->SetCollisionProfileName("BlockOnlyPlayer");

	Roof = CreateDefaultSubobject<UBoxComponent>(TEXT("Roof"));
	Roof->SetupAttachment(RootComponent);
	Roof->SetCollisionProfileName("BlockOnlyPlayer");

}

// Called when the game starts or when spawned
void ARoofVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoofVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

