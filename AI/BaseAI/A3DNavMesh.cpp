// Fill out your copyright notice in the Description page of Project Settings.


#include "A3DNavMesh.h"

// Sets default values
AA3DNavMesh::AA3DNavMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	root->SetupAttachment(RootComponent);
	
	Bounds = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounds"));
	Bounds->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AA3DNavMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA3DNavMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

