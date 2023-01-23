// Fill out your copyright notice in the Description page of Project Settings.


#include "WallCreature.h"

AWallCreature::AWallCreature()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetCollisionProfileName("OverlapOnlyPlayer");
	CollisionSphere->SetSphereRadius(500);
	CollisionSphere->SetHiddenInGame(false);

	ScaleTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ScaleTimeline"));
	ScaleUpdateFunction.BindUFunction(this, FName("ScaleFloatReturn"));
	ScaleFinishedFunction.BindUFunction(this, FName("ScaleFinished"));
	
}

void AWallCreature::BeginPlay()
{
	Super::BeginPlay();

	this->GetMesh()->SetWorldScale3D(FVector(0));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWallCreature::OnSphereBeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AWallCreature::OnSphereEndOverlap);

	if(ScaleCurve->IsValidLowLevelFast())
	{
		ScaleTimeline->AddInterpFloat(ScaleCurve, ScaleUpdateFunction, FName("Float"));
		ScaleTimeline->SetTimelineFinishedFunc(ScaleFinishedFunction);
		ScaleTimeline->SetLooping(false);
		ScaleTimeline->SetIgnoreTimeDilation(true);
	}
}

void AWallCreature::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player") && PlayerInside == false)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("PlayerEntered")));
		PlayerInside = true;
		ScaleTimeline->Play();
	}
}

void AWallCreature::OnSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->ActorHasTag("Player") && PlayerInside == true)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("PlayerExited")));
		PlayerInside = false;
		ScaleTimeline->Reverse();
	}
}

void AWallCreature::ScaleFloatReturn(float value)
{
	this->GetMesh()->SetWorldScale3D(FVector(value));
}

void AWallCreature::ScaleFinished()
{
}
