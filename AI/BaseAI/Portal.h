// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class DESCENTIUM_API APortal : public AActor
{
	GENERATED_BODY()

	USceneComponent* SceneComponent;

public:
	// Sets default values for this actor's properties
	APortal();

	UNiagaraSystem* PortalOpening;
	UNiagaraSystem* PortalOpen;
	UNiagaraSystem* PortalClosing;

	UNiagaraComponent* PortalPtr;
	FTimerHandle OpeningPortalTimer;

	FTimerHandle ClosingPortalTimer;

	FTimerHandle PortalLifetime;

	UFUNCTION()
	void OpenPortal();
	void OpeningPortalFinished();
	void ClosePortalDelay(float Duration);

	UFUNCTION()
	void OpenPortalLifetime(float Duration);
	
	UFUNCTION()
	void ClosePortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
