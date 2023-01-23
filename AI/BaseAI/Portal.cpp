// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "NiagaraFunctionLibrary.h"


// Sets default values
APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PortalOpeningOBJ(TEXT("NiagaraSystem'/Game/OrganisedContent/ArtAssets/VFX/VFX_Systems/Turret_Enemy/Turret_Portal/Turret_Portal_Open_NS.Turret_Portal_Open_NS'"));
	PortalOpening = PortalOpeningOBJ.Object;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PortalOpenOBJ(TEXT("NiagaraSystem'/Game/OrganisedContent/ArtAssets/VFX/VFX_Systems/Turret_Enemy/Turret_Portal/Turret_Portal_Still_NS.Turret_Portal_Still_NS'"));
	PortalOpen = PortalOpenOBJ.Object;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PortalClosingOBJ(TEXT("NiagaraSystem'/Game/OrganisedContent/ArtAssets/VFX/VFX_Systems/Turret_Enemy/Turret_Portal/Turret_Portal_Close_NS.Turret_Portal_Close_NS'"));
	PortalClosing = PortalClosingOBJ.Object;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}

void APortal::OpenPortal()
{
	if(PortalOpening->IsValidLowLevelFast())
	{
		PortalPtr = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PortalOpening, this->GetActorLocation(), this->GetActorRotation(), this->GetActorScale());
		GetWorld()->GetTimerManager().SetTimer(OpeningPortalTimer, this, &APortal::OpeningPortalFinished, 0.5f, false);
	}
}

void APortal::OpenPortalLifetime( float Duration)
{
	if(PortalOpening->IsValidLowLevelFast())
	{
		PortalPtr = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PortalOpening, this->GetActorLocation(), this->GetActorRotation(), this->GetActorScale());
		GetWorld()->GetTimerManager().SetTimer(OpeningPortalTimer, this, &APortal::OpeningPortalFinished, 0.5f, false);
	}
	GetWorld()->GetTimerManager().SetTimer(PortalLifetime, this, &APortal::ClosePortal, Duration, false);
}

void APortal::OpeningPortalFinished()
{
	if(PortalPtr->IsValidLowLevelFast())
	{
		if(PortalOpen->IsValidLowLevelFast())
		{
			PortalPtr = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PortalOpen, this->GetActorLocation(), this->GetActorRotation(), this->GetActorScale());
		}
	}
}

void APortal::ClosePortalDelay(float Duration)
{
	GetWorld()->GetTimerManager().SetTimer(ClosingPortalTimer, this, &APortal::ClosePortal,Duration, false);
}

void APortal::ClosePortal()
{
	if(PortalPtr->IsValidLowLevelFast())
	{
		PortalPtr->DestroyComponent();
	}
	if(PortalClosing->IsValidLowLevelFast())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PortalClosing, this->GetActorLocation(), this->GetActorRotation(), this->GetActorScale());
	}
	Destroy();
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

