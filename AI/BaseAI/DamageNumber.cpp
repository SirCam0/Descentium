// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageNumber.h"

#include "BaseAI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADamageNumber::ADamageNumber()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageNumberWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	RootComponent = DamageNumberWidgetComponent;
}

void ADamageNumber::ExtendLifetime(int NewValue, float NewLifetime)
{
	ExtendLifetimeBlueprintDelegate(NewValue,NewLifetime);
	GetWorld()->GetTimerManager().SetTimer(LifetimeTimerHandle, this, &ADamageNumber::LifetimeTimerEndEvent, NewLifetime, false);
	Value = NewValue;
}

void ADamageNumber::LifetimeTimerEndEvent()
{
	StartNiagara();
	if(Owner->IsValidLowLevelFast())
	{
		Owner->CurrentDamageNumber = nullptr;
	}
	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &ADamageNumber::DelayTimerEndEvent, 1, false);
}

void ADamageNumber::DelayTimerEndEvent()
{
	Destroy();
}

// Called when the game starts or when spawned
void ADamageNumber::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(LifetimeTimerHandle, this, &ADamageNumber::LifetimeTimerEndEvent, 2, false);
}

// Called every frame
void ADamageNumber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorLocation();
	const FRotator LookAtPlayerRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerLocation);
	this->SetActorRotation(LookAtPlayerRotation);
}

