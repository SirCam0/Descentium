// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AI/BaseAI/StructsAndEnums/Scenario.h"
#include "SaveRunStructs/RunSaveStruct.h"
#include "SaveRunStructs/Ability/ChainMode.h"
#include "RogueLiteGameInstanceParent.generated.h"



/**
 * 
 */
UCLASS()
class DESCENTIUM_API URogueLiteGameInstanceParent : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void BeginRun();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BeginRunBP();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddTotalDamageBP(int Amount);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FScenario> Stage1Scenarios;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FScenario> Stage2Scenarios;

	TArray<FScenario> UnUsedStage1Scenarios;

	TArray<FScenario> UnUsedStage2Scenarios;

	UFUNCTION(BlueprintCallable)
	void ShuffleScenarios();

	UFUNCTION(BlueprintCallable)
	void ResetUnUsedScenarios();

	UFUNCTION(BlueprintCallable)
	FScenario GetStage1Scenario();

	UFUNCTION(BlueprintCallable)
	FScenario GetStage2Scenario();

	UFUNCTION(BlueprintCallable)
	void SavePlayerMidRun(int PermaCurrency, int TempCurrency, int MaxHealth, int Health, UStruct* TempShopData,
	                      UStruct* AllPlayerUpgrades, float MaxWalkSpeed, float JumpZVelocity,TEnumAsByte<EquippedAbility> EquippedAbility,
	                      TEnumAsByte<DashModeNew> DashType, int DashLevel, TEnumAsByte<ChainMode> ChainType, int ChainLevel, FWeaponSaveStruct WeaponSaveStuff,
	                      FNewWeaponStats CurrentWeaponStats, TArray<FNew_WeaponUpgrades_Lvl_Cost> AvailableWeaponUpgrades,
	                      TArray<FNewDoorUpgradesStruct> UpgradeList, TEnumAsByte<NewTrinketList> EquippedTrinket, int CurrentTrinketUses,FNewMasterTrinketSaveData
	                      TrinketSaveStuff);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FRunSaveStruct CurrentPlayerStatistics;
	
};
