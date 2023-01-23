// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "DamageNumber.generated.h"

class ABaseAI;
UCLASS()
class DESCENTIUM_API ADamageNumber : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageNumber();

	UFUNCTION()
	void ExtendLifetime(int NewValue, float NewLifetime);

	UFUNCTION(BlueprintImplementableEvent)
	void ExtendLifetimeBlueprintDelegate(int NewValue, float NewLifetime);

	UFUNCTION(BlueprintImplementableEvent)
	void StartNiagara();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* DamageNumberWidgetComponent;
	
	ABaseAI* Owner;
	
	FTimerHandle LifetimeTimerHandle;
	virtual void LifetimeTimerEndEvent();
	
	FTimerHandle DelayTimerHandle;
	virtual void DelayTimerEndEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void SetText(int Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCritAnimation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
