// Fill out your copyright notice in the Description page of Project Settings.


#include "WormBossAI.h"

#include "NavMeshNode.h"
#include "Portal.h"
#include "WormBossMovementVolume.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AWormBossAI::AWormBossAI()
{
	this->GetCharacterMovement()->GravityScale = 0;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeadOBJ(TEXT("StaticMesh'/Game/OrganisedContent/ArtAssets/Characters/TPAI/Models/TpEnemy_SM.TpEnemy_SM'"));
	Head = HeadOBJ.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyOBJ(TEXT("StaticMesh'/Game/OrganisedContent/ArtAssets/Characters/TPAI/Models/TpBossMidPiece.TpBossMidPiece'"));
	Body = BodyOBJ.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TailOBJ(TEXT("StaticMesh'/Game/OrganisedContent/ArtAssets/Characters/TPAI/Models/TpBossEndPiece.TpBossEndPiece'"));
	Tail = TailOBJ.Object;
}

void AWormBossAI::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimer, this, &AWormBossAI::AfterSpawnDelay, SpawnDelay, false);
	FActorSpawnParameters SpawnParams;
	Spline = GetWorld()->SpawnActor<AWormBossSpline>(AWormBossSpline::StaticClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	Spline->Rail->ClearSplinePoints();
	Spline->Rail->AddSplineWorldPoint(this->GetActorLocation()-this->GetActorForwardVector()*100);
	Spline->Rail->AddSplineWorldPoint(this->GetActorLocation()+this->GetActorForwardVector()*2000);
	/**
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, ANavMeshNode::StaticClass(), Actors);
	NavNodes.Reserve(Actors.Num());
	for(AActor* Actor: Actors)
	{
		if(Actor->GetClass()->ImplementsInterface(UNavMeshNodeInterface::StaticClass()))
		{
			NavNodes.Add(INavMeshNodeInterface::Execute_GetNavMeshNodeREF(Actor));
		}
	}
	//Build Full Worm
	/**
	for (int i = 0; i < Sections+2; i++)
	{
		UStaticMeshComponent * NewMesh = NewObject<UStaticMeshComponent>(this);
		NewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		NewMesh->RegisterComponent();
		BodyParts.Add(NewMesh);
	}
	for (int n = BodyParts.Num()-1; n >= 0; n--)
	{
		float DistanceModifier = 0;
		if(n == 0)
		{
			DistanceModifier = (SectionSize*n)+SectionSize;
		}
		else{
			DistanceModifier = SectionSize*n;
		}
		BodyParts[n]->SetWorldLocation(Spline->Rail->GetLocationAtDistanceAlongSpline(Spline->Rail->GetSplineLength()-DistanceModifier, ESplineCoordinateSpace::World));
		BodyParts[n]->SetWorldRotation(Spline->Rail->GetRotationAtDistanceAlongSpline(Spline->Rail->GetSplineLength()-DistanceModifier, ESplineCoordinateSpace::World)+FRotator(0,90,0));
		if(n == 0)
		{
			BodyParts[n]->SetStaticMesh(Head);
		}
		else if(n == BodyParts.Num()-1)
		{
			BodyParts[n]->SetStaticMesh(Tail);
		}
		else
		{
			BodyParts[n]->SetStaticMesh(Body);
		}
	}
	*/
}

void AWormBossAI::AfterSpawnDelay()
{
	FActorSpawnParameters SpawnParams;
	StartPortal = GetWorld()->SpawnActor<APortal>(APortal::StaticClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	StartPortal->OpenPortal();
	GetWorld()->GetTimerManager().SetTimer(MovementTimer,this,&AWormBossAI::MoveAlongSplineInterval, 0.01, true, 1);
}

void AWormBossAI::SetMoveToLocation(FVector location)
{
	ChoosePathBP(location);
}

void AWormBossAI::Grow(int Amount){
	this->Sections += Amount;
}

void AWormBossAI::MoveAlongSplineInterval()
{
	if(moving)
	{
		const float SplineLength = Spline->Rail->GetSplineLength();
		//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, FString::Printf(TEXT("%f"), SplineLength + Sections*SectionSize));
		if(CurrentDistanceAlongSpline < SplineLength + Sections*SectionSize)
		{
			CurrentDistanceAlongSpline += MovementSpeed;
		}
		else if(!DoOnce2)
		{
			DoOnce2 = true;
			EndPortal->ClosePortalDelay(0.65);
		}
	
		//Add any new Sections that need adding
		if(CurrentDistanceAlongSpline/SectionSize <= Sections)
		{
			CurrentSections = CurrentDistanceAlongSpline/SectionSize;
		}
		else
		{
			CurrentSections = Sections;
		}
		const int SectionsToAdd = CurrentSections - BodyParts.Num()-1;
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("%i"), SectionsToAdd));
		if(SectionsToAdd > 0)
		{
			for(int i = SectionsToAdd; i >= 0; i--)
			{
				UStaticMeshComponent * NewMesh = NewObject<UStaticMeshComponent>(this);
				NewMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
				//NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				NewMesh->RegisterComponent();
				NewMesh->SetWorldScale3D(FVector(1,1,1));
				BodyParts.Add(NewMesh);
				if(BodyParts.Num() == Sections)
				{
					if(TailPart->IsValidLowLevelFast())
					{
						TailPart->SetStaticMesh(Body);
					}
					NewMesh->SetStaticMesh(Tail);
					StartPortal->ClosePortalDelay(1);
					TailPart = NewMesh;
				}
				else if(BodyParts.Num() == 1)
				{
					NewMesh->SetStaticMesh(Head);
				}
				else{
					NewMesh->SetStaticMesh(Body);
				}
			}
		}
		
		int Index = 0;
		for (UStaticMeshComponent* BodyPart : BodyParts)
		{
			float Modifier = Index*SectionSize;
			if(Index == 0)
			{
				//Modifier += SectionSize;
				//GEngine->AddOnScreenDebugMessage(-1,0.1,FColor::Red,FString::Printf(TEXT("SplineLength:%f Distance:%f"), SplineLength - 600, CurrentDistanceAlongSpline));
				if(CurrentDistanceAlongSpline > SplineLength-600)
				{
					if(teleporting)
					{
						FActorSpawnParameters SpawnParams;
						if(!DoOnce)
						{
							DoOnce = true;
							EndPortal = GetWorld()->SpawnActor<APortal>(APortal::StaticClass(), Spline->Rail->GetWorldLocationAtDistanceAlongSpline(Spline->Rail->GetSplineLength()-SectionSize), Spline->Rail->GetWorldRotationAtDistanceAlongSpline(Spline->Rail->GetSplineLength()-SectionSize), SpawnParams);
							EndPortal->OpenPortal();
						}
					}
					else
					{
						PickNewMoveToLocation();
					}
				}
			}
			if(CurrentDistanceAlongSpline-Modifier > SplineLength)
			{
				if(teleporting)
				{
					BodyParts[Index]->SetVisibility(false);
				}
			}
			BodyParts[Index]->SetWorldLocation(Spline->Rail->GetWorldLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline-Modifier));
			BodyParts[Index]->SetWorldRotation(Spline->Rail->GetWorldRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline-Index*SectionSize));
			Index++;
		}
	}
}

void AWormBossAI::TeleportToNewLocation(FVector location, FRotator rotation)
{
}

void AWormBossAI::PickNewMoveToLocation()
{
	FVector NewLocation;
	AWormBossMovementVolume* MovementVolume = Cast<AWormBossMovementVolume>(UGameplayStatics::GetActorOfClass(this, AWormBossMovementVolume::StaticClass()));
	if(MovementVolume->IsValidLowLevelFast())
	{
		float distance = 0;
		while(distance < 1000)
		{
			NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(MovementVolume->BoxComponent->Bounds.Origin,MovementVolume->BoxComponent->Bounds.BoxExtent);
			distance = FVector::Distance(BodyParts[0]->GetComponentLocation(),NewLocation);
		}
		SetMoveToLocation(NewLocation);
	}
}




