// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueLiteGameInstanceParent.h"


void URogueLiteGameInstanceParent::BeginRun()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("BeginingRun")));
	ResetUnUsedScenarios();
	BeginRunBP();
}

void URogueLiteGameInstanceParent::ShuffleScenarios()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Shuffling")));
	if(Stage1Scenarios.Num() > 0)
	{
		int32 LastIndex = Stage1Scenarios.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Stage1Scenarios.Swap(i, Index);
			}
		}
	}
	if(Stage2Scenarios.Num() > 0)
	{
		int32 LastIndex = Stage2Scenarios.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Stage2Scenarios.Swap(i, Index);
			}
		}
	}
}

//Call at the beginning of a run
void URogueLiteGameInstanceParent::ResetUnUsedScenarios()
{
	ShuffleScenarios();
	UnUsedStage1Scenarios = Stage1Scenarios;
	UnUsedStage2Scenarios = Stage2Scenarios;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), UnUsedStage1Scenarios.Num()));
}

FScenario URogueLiteGameInstanceParent::GetStage1Scenario()
{
	
	const int Index = FMath::FRandRange(0,UnUsedStage1Scenarios.Num());
	if(UnUsedStage1Scenarios.IsValidIndex(Index))
	{
		FScenario Scenario = UnUsedStage1Scenarios[Index];
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), Scenario.Waves[0].Enemies[0].Number));
		UnUsedStage1Scenarios.RemoveAt(Index);
		return Scenario;
	}
	FScenario Scenario;
	return Scenario;
}

FScenario URogueLiteGameInstanceParent::GetStage2Scenario()
{
	
	const int Index = FMath::FRandRange(0,UnUsedStage2Scenarios.Num());
	if(UnUsedStage2Scenarios.IsValidIndex(Index))
	{
		FScenario Scenario = UnUsedStage2Scenarios[Index];
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("number: %i"), Scenario.Waves[0].Enemies[0].Number));
		UnUsedStage2Scenarios.RemoveAt(Index);
		return Scenario;
	}
	FScenario Scenario;
	return Scenario;
}

void URogueLiteGameInstanceParent::SavePlayerMidRun(int PermaCurrency, int TempCurrency, int MaxHealth, int Health, UStruct* TempShopData,
		UStruct* AllPlayerUpgrades, float MaxWalkSpeed, float JumpZVelocity, TEnumAsByte<EquippedAbility> EquippedAbility, TEnumAsByte<DashModeNew> DashType, int DashLevel, TEnumAsByte<ChainMode> ChainType,
		int ChainLevel, FWeaponSaveStruct WeaponSaveStuff, FNewWeaponStats CurrentWeaponStats, TArray<FNew_WeaponUpgrades_Lvl_Cost> AvailableWeaponUpgrades, TArray<FNewDoorUpgradesStruct> UpgradeList, TEnumAsByte<NewTrinketList> EquippedTrinket,
		int CurrentTrinketUses, FNewMasterTrinketSaveData TrinketSaveStuff)
{
	this->CurrentPlayerStatistics.PermaCurrency = PermaCurrency;
	this->CurrentPlayerStatistics.TempCurrency = TempCurrency;
	this->CurrentPlayerStatistics.MaxHealth = MaxHealth;
	this->CurrentPlayerStatistics.Health = Health;
	this->CurrentPlayerStatistics.TempShopData = TempShopData;
	this->CurrentPlayerStatistics.AllPlayerUpgrades = AllPlayerUpgrades;
	this->CurrentPlayerStatistics.MaxWalkSpeed = MaxWalkSpeed;
	this->CurrentPlayerStatistics.JumpZVelocity = JumpZVelocity;
	this->CurrentPlayerStatistics.EquippedAbility = EquippedAbility;
	this->CurrentPlayerStatistics.DashMode = DashType;
	this->CurrentPlayerStatistics.DashLevel = DashLevel;
	this->CurrentPlayerStatistics.ChainType = ChainType;
	this->CurrentPlayerStatistics.ChainLevel = ChainLevel;
	this->CurrentPlayerStatistics.WeaponSaveStuff = WeaponSaveStuff;
	this->CurrentPlayerStatistics.CurrentWeaponStats = CurrentWeaponStats;
	this->CurrentPlayerStatistics.AvailableWeaponUpgrades = AvailableWeaponUpgrades;
	this->CurrentPlayerStatistics.UpgradeList = UpgradeList;
	this->CurrentPlayerStatistics.EquippedTrinket = EquippedTrinket;
	this->CurrentPlayerStatistics.CurrentTrinketUses = CurrentTrinketUses;
	this->CurrentPlayerStatistics.TrinketSaveStuff = TrinketSaveStuff;
}
