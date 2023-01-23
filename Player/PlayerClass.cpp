// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerClass.h"

#include "Descentium/AI/Pickups/Pickup.h"
#include "Descentium/AI/Pickups/PickupInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerClass::APlayerClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRadiusSphere"));
	PickupRadiusSphere->SetupAttachment(RootComponent);
	PickupRadiusSphere->InitSphereRadius(PickupSphereRadius);
	PickupRadiusSphere->SetCollisionProfileName("PlayerPickupCollision");

	LandedTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("LandedTimeline"));
	LandedTimelineUpdateFunction.BindUFunction(this, FName("LandedTimelineInterval"));
	LandedTimelineFinished.BindUFunction(this, FName("LandedTimelineFinishedFunc"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveOBJ(TEXT("CurveFloat'/Game/OrganisedContent/Player/FallLandingCurve.FallLandingCurve'"));
	LandedTimelineCurve = CurveOBJ.Object;
	
}

void APlayerClass::ArmsSway(float DeltaTime, USkeletalMeshComponent* ArmsPtr)
{
	if(!PlayingLandAnim)
	{
		if(!Arms->IsValidLowLevelFast())
		{
			Arms = ArmsPtr;
		}
		const float MaxSway = 5;
		const float Turn = this->InputComponent->GetAxisValue("Turn");
		const float LookUp = this->InputComponent->GetAxisValue("Look Up");
		float MoveUp = UKismetMathLibrary::MapRangeClamped(this->GetCharacterMovement()->GetLastUpdateVelocity().Z, -1500, 1500, -6, 6);
		if(Falling && !this->GetCharacterMovement()->IsFalling())
		{
			//landed
			LandedTimeline->PlayFromStart();
		}
		Falling = this->GetCharacterMovement()->IsFalling();
		const FRotator FinalRotator = FRotator((LookUp*-1+MoveUp)*MaxSway,Turn*-1*MaxSway,Turn*-1*MaxSway);
		const FRotator InitalRotator = FRotator(0);
		const FRotator Target = FRotator((InitalRotator.Pitch+FinalRotator.Pitch)*-1,(InitalRotator.Yaw+FinalRotator.Yaw),(InitalRotator.Roll+FinalRotator.Roll));
		const FRotator PreBreak = UKismetMathLibrary::RInterpTo(Arms->GetRelativeRotation(), Target, DeltaTime, 1);
		const float X = UKismetMathLibrary::FClamp(PreBreak.Roll,MaxSway*-1,MaxSway);
		const float Y = UKismetMathLibrary::FClamp(PreBreak.Pitch,MaxSway*-1,MaxSway);
		const float Z = UKismetMathLibrary::FClamp(PreBreak.Yaw,MaxSway*-1,MaxSway);
		Arms->SetRelativeRotation(FRotator(Y,Z,X), false, nullptr, ETeleportType::None);
	}
}

void APlayerClass::LandedTimelineInterval(float value)
{
	if(!PlayingLandAnim)
	{
		PlayingLandAnim = true;
	}
	FRotator InitialRot = Arms->GetRelativeRotation();
	FRotator TargetRot = FRotator(value, InitialRot.Yaw, InitialRot.Roll);
	Arms->SetRelativeRotation(TargetRot, false, nullptr, ETeleportType::None);
}

void APlayerClass::LandedTimelineFinishedFunc()
{
	PlayingLandAnim = false;
}

// Called when the game starts or when spawned
void APlayerClass::BeginPlay()
{
	Super::BeginPlay();
	PickupRadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerClass::OnPickupSphereBeginOverlap);
	
	if(LandedTimelineCurve->IsValidLowLevelFast())
	{
		LandedTimeline->AddInterpFloat(LandedTimelineCurve, LandedTimelineUpdateFunction, FName("float"));
		LandedTimeline->SetTimelineFinishedFunc(LandedTimelineFinished);
		LandedTimeline->SetLooping(false);
		LandedTimeline->SetIgnoreTimeDilation(false);
	}
}

void APlayerClass::OnPickupSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsValidLowLevelFast())
	{
		if(OtherActor->ActorHasTag("Pickup") /**&& !OverlappedPickups.Contains(OtherActor)*/)
		{
			OverlappedPickups.AddUnique(OtherActor);
			if(OtherActor->GetClass()->ImplementsInterface(UPickupInterface::StaticClass()))
			{
				APickup* Pickup = IPickupInterface::Execute_GetBasePickupREF(OtherActor);
				Pickup->GoToPlayer();
			}
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,FString::Printf(TEXT("PickupOverlapped")));
		}
	}
}

// Called every frame
void APlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

