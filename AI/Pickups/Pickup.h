// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "PickupInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Pickup.generated.h"

UCLASS()
class DESCENTIUM_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()

	virtual APickup* GetBasePickupREF_Implementation() override;



public:
	// Sets default values for this actor's properties
	APickup();
	void GoToPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* TrailEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* ParticleVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void GiveCurrency();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrencyValue = 1;

	FTimerHandle GoToPlayerTimer;

	void GoToPlayerInterval();

	ACharacter* Player;

	float DeltaSeconds;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlapped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                 FVector NormalImpulse, const FHitResult& Hit);
	void StartDestroyPickup();
	void EndDestroyPickup();

	FTimerHandle DestroyTimerHandle;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
