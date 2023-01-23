// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageNumber.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraSystem.h"
#include "NonDoorSpawnLocation.h"
#include "Components/TimelineComponent.h"
#include "Descentium/MyBaseAIInterface.h"
#include "Descentium/RogueLiteGameInstanceParent.h"
#include "Engine/DataTable.h"
#include "StructsAndEnums/HitReactionThresholds.h"
#include "StructsAndEnums/TokenTypeEnum.h"
#include "StructsAndEnums/EnemyType.h"
#include "BaseAI.generated.h"

class AArtificialIntelligenceManager;
class ASpawnDoorsManager;
UCLASS(Blueprintable)
class DESCENTIUM_API ABaseAI : public ACharacter, public IMyBaseAIInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	AArtificialIntelligenceManager* AITokenManager;
	
	ABaseAI* GetMyBaseAIREF_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateRunStats();
	
	// Sets default values for this character's properties
	ABaseAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TempCurrencyToDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PermaCurrencyToDrop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* CritSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* HealthBar;

	UPROPERTY()
	UStaticMeshComponent* TestMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	TArray<TEnumAsByte<TokenTypeEnum>> UsedTokenTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	TArray<TEnumAsByte<TokenTypeEnum>> CurrentHeldTokens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	int Health = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	int MaxHealth = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	int hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseVariables")
	FHitReactionThresholds HitReactionThresholds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* TwitchAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* FalterAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* StaggerAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProgrammingTemps")
	int DamageTotal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProgrammingTemps")
	ADamageNumber* CurrentDamageNumber;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* DamageNumberBlueprint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* TempCurrencyBlueprint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* PermaCurrencyBlueprint;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProgrammingTemps")
	float DamageNumberLifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* ImpactVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* DeathVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanBeHooked = true;

	UPROPERTY()
	FTimerHandle ApplyDamageTimerHandle;
	
	UFUNCTION()
	virtual void ResetApplyDamageTimerHandle();

	UPROPERTY(BlueprintReadWrite)
	bool bStunned;
	
	UPROPERTY()
	FTimerHandle StunnedTimerHandle;
	
	UFUNCTION()
	virtual void StunnedTimerComplete();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* BleedVFX;

	UPROPERTY()
	UNiagaraComponent* CurrentBleedVFX;

	UFUNCTION(BlueprintCallable)
	void Bleed(float BleedPulseInterval, float NumberOfIntervals, int DamagePerInterval, FVector HitLocation, FVector HitNormal);

	UPROPERTY()
	FVector BleedingRelativeLocation;
	
	UPROPERTY()
	float BleedCount;
	
	UPROPERTY()
	float BleedInterval;
	
	UPROPERTY()
	int BleedDamage;
	
	UPROPERTY()
	FTimerHandle BleedTimerHandle;
	
	UFUNCTION()
	virtual void BleedTimerInterval();

	UFUNCTION(BlueprintCallable)
	void SetSpeed(float Duration, float SpeedPercentage);
	
	UFUNCTION()
	void SetSpeedTimerComplete();
	
	UFUNCTION()
	void SmartJump(FVector StartLocation, FVector EndLocation, FVector EndLocationVelocity);
	
	UFUNCTION()
	void ReceiveToken(TokenTypeEnum TokenType, float HoldForDuration);
	
	UFUNCTION()
	void ReturnTokenAfterTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedModifier;
	
	UPROPERTY()
	bool Slowed;
	
	UPROPERTY()
	float MaxWalkSpeedTemp;
	
	UPROPERTY()
	FTimerHandle SetSpeedTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkForwardFromStartDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "BaseVariables")
	float CritModifier = 1.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AwaitingToken = false;

	UPROPERTY()
	FTimerHandle TokenUseTimerHandle;
	
	TokenTypeEnum LastReceivedToken;

	UPROPERTY()
	ANonDoorSpawnLocation* NonDoorLocation = nullptr;

	UPROPERTY()
	ACharacter* PlayerCharacter;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	bool StaggerDoOnce = false;
	
	UPROPERTY()
	bool FalterDoOnce = false;

	UFUNCTION(BlueprintCallable)
	virtual void Death(bool CritDeath);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDeath(bool CritDeath);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Twitch();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Falter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Stagger();

	UFUNCTION(BlueprintCallable)
	void ReturnAllTokens();

	UFUNCTION(BlueprintCallable)
	FVector GetPredictedLocation();

	UFUNCTION(BlueprintCallable)
	virtual void Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit);

	UFUNCTION()
	void ApplyCombo(int Damage);

	UFUNCTION()
	void ResetCombo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* CritSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Stunned(float Duration);
	
	UFUNCTION(BlueprintCallable)
	void TimeDilate(float Duration, float Dilation);

	UPROPERTY(BlueprintReadWrite)
	ASpawnDoorsManager* WaveManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTableBaseValues;

	UPROPERTY()
	class UTimelineComponent* DisolveTimeline;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool DisolveOnDeath = true;

	UFUNCTION()
	void DisolveTimelineFloatReturn(float value);
	FOnTimelineFloat DisolveTimelineUpdateFunction{};

	UFUNCTION()
	void DisolveTimelineFinished();
	FOnTimelineEvent DisolveTimelineFinishedFunction{};

	UPROPERTY(EditAnywhere, Category = "DisolveTimeline")
	class UCurveFloat* DisolveTimelineCurve;

	UPROPERTY(BlueprintReadWrite)
	bool Dead = false;

	UPROPERTY(BlueprintReadWrite)
	TArray<ABaseAI*> DamageSharedActors;

	bool DamageSharing = false;

	UFUNCTION(BlueprintCallable)
	void DoDamageSharing(TArray<ABaseAI*> Enemies);

	UFUNCTION(BlueprintCallable)
	void StopDamageSharing();

	UPROPERTY(BlueprintReadWrite)
	bool Highlighting = false;

	UPROPERTY(BlueprintReadWrite)
	bool HighlightOveride = false;

	UFUNCTION(BlueprintCallable)
	void Highlight(bool highlight);

	UPROPERTY(BlueprintReadWrite)
	int ShieldingMaxHP = 0;

	UPROPERTY(BlueprintReadWrite)
	int ShieldHP = 0;

	URogueLiteGameInstanceParent* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* ShieldMaterial;

	UFUNCTION(BlueprintCallable)
	void SetShield();
};
