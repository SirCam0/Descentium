// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "PlayerClass.generated.h"

UCLASS()
class DESCENTIUM_API APlayerClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerClass();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupRadiusSphere;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Pickups)
	float PickupSphereRadius = 500.f;
	TArray<AActor*> OverlappedPickups;

	// Arm Sway Stuff
	USkeletalMeshComponent* Arms;
	
	UFUNCTION(BlueprintCallable)
	void ArmsSway(float DeltaTime, USkeletalMeshComponent* Arms);
	
	bool Falling = false;

	bool PlayingLandAnim;

	class UTimelineComponent* LandedTimeline;

	UFUNCTION()
	void LandedTimelineInterval(float value);
	FOnTimelineFloat LandedTimelineUpdateFunction{};

	UFUNCTION()
	void LandedTimelineFinishedFunc();
	FOnTimelineEvent LandedTimelineFinished{};

	UPROPERTY(EditAnywhere, Category = "LandedTimeline")
	class UCurveFloat* LandedTimelineCurve;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPickupSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
