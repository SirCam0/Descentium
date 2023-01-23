// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "NiagaraComponent.h"
#include "Descentium/Player/PlayerClass.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


APickup* APickup::GetBasePickupREF_Implementation()
{
	return this;
}

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Tags.Add("Pickup");

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetCollisionProfileName("Pickup");

	ParticleVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	ParticleVFX->SetupAttachment(RootComponent);
	
	TrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	TrailEffect->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ParticleMovement");
	ProjectileMovementComponent->Bounciness = 0.6;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Friction = 0.4;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->ProjectileGravityScale = 1.5;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 0;
	ProjectileMovementComponent->bIsHomingProjectile = true;
}

void APickup::GoToPlayer()
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("Going to player")));
	Player = UGameplayStatics::GetPlayerCharacter(this,0);
	GetWorld()->GetTimerManager().SetTimer(GoToPlayerTimer, this, &APickup::GoToPlayerInterval, 0.01, true);
}

void APickup::GoToPlayerInterval()
{
	if (Player->IsValidLowLevelFast())
	{
		FVector CurrentVector = UKismetMathLibrary::VInterpTo(this->GetActorLocation(), Player->GetActorLocation(), DeltaSeconds, 7);
		FHitResult HitResult;
		this->SetActorLocation(CurrentVector, true, &HitResult);
	}
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlapped);
	float RandX = FMath::RandRange(100,300);
	if(FMath::RandBool())
	{
		RandX = RandX*-1;
	}
	float RandY = FMath::RandRange(100,300);
	if(FMath::RandBool())
	{
		RandY = RandY*-1;
	}
	float RandZ = FMath::RandRange(250,500);
	ProjectileMovementComponent->Velocity = FVector(RandX,RandY,RandZ);
}

void APickup::OnSphereOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("OverlappedPlayer")));
	if(OtherComp->ComponentTags.Contains("PlayerCollisionCapsule"))
	{
		StartDestroyPickup();
	}
}

void APickup::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("HitPlayer")));
	if(OtherActor->Tags.Contains("Player"))
	{
		StartDestroyPickup();
	}
}

void APickup::StartDestroyPickup()
{
	GiveCurrency();
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleVFX->SetHiddenInGame(true);
	ProjectileMovementComponent->Velocity = FVector(0);
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->HomingAccelerationMagnitude = 0;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,this, &APickup::EndDestroyPickup, 3, false);
}

void APickup::EndDestroyPickup()
{
	Destroy();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	this->DeltaSeconds = DeltaTime;
	Super::Tick(DeltaTime);
}

