// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulAI.h"

#include "Chaos/GeometryParticlesfwd.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ASimulAI* ASimulAI::GetSimulAIREF_Implementation()
{
	return this;
}

ASimulAI::ASimulAI()
{
	ChargeWedge = CreateDefaultSubobject<UBoxComponent>(TEXT("ChargeWedge"));
	ChargeWedge->SetupAttachment(RootComponent);
	ChargeWedge->SetRelativeRotation(FRotator(0,45,0));
	ChargeWedge->SetBoxExtent(FVector(70,70,120));
	ChargeWedge->SetRelativeLocation(FVector(70,0,0));
	ChargeWedge->SetCollisionProfileName("SimulChargeWedge");
	ChargeWedge->SetCanEverAffectNavigation(false);
	ChargeWedge->SetHiddenInGame(true);
	
}

void ASimulAI::BeginPlay()
{
	Super::BeginPlay();
	//ChargeWedge->OnComponentHit.AddDynamic(this,&ASimulAI::ChargeWedgeHit);
	//ChargeWedge->OnComponentBeginOverlap.AddDynamic(this,&ASimulAI::ChargeWedgeOverlapped);
}

void ASimulAI::ChargeWedgeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("Hit")));
	if(Charging)
	{
		if(OtherActor->IsValidLowLevelFast())
		{
			Cast<ACharacter>(OtherActor)->LaunchCharacter(Hit.ImpactNormal*((Values.ChargeKnockback)-1), false, false);
			if(OtherActor->ActorHasTag("Player") && !HitPlayerDoOnce)
			{
				HitPlayerDoOnce = true;
				PlayerHit();
			}
			else if (!OtherActor->ActorHasTag("Enemy"))
			{
				EndCharge();
			}
		}
	}
}

void ASimulAI::ChargeWedgeOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("Overlap")));
	if(Charging)
	{
		if(OtherActor->IsValidLowLevelFast())
		{
			if(OtherActor != this)
			{
				if (!(OtherActor->ActorHasTag("Player")))
				{
					EndCharge();
				}
			}
		}
	}
}

