// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Ability/ChainMode.h"
#include "Ability/DashMode.h"
#include "Descentium/AI/BaseAI/StructsAndEnums/EquippedAbility.h"
#include "Door/NewDoorUpgradesStruct.h"
#include "Trinket/NewMasterTrinketSaveData.h"
#include "Trinket/NewTrinketList.h"
#include "Weapon/WeaponSaveStruct.h"
#include "Weapon/NewWeaponStats.h"
#include "Weapon/New_WeaponUpgrades_LVL_Cost.h"
#include "RunSaveStruct.Generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRunSaveStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	int PermaCurrency;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	int TempCurrency;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	int MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	int Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	UStruct* TempShopData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	UStruct* AllPlayerUpgrades;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	float MaxWalkSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Player)
	float JumpZVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Ability)
	TEnumAsByte<EquippedAbility> EquippedAbility;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Ability)
	TEnumAsByte<DashModeNew> DashMode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Ability)
	int DashLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Ability)
	TEnumAsByte<ChainMode> ChainType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Ability)
	int ChainLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Weapon)
	FWeaponSaveStruct WeaponSaveStuff;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Weapon)
	FNewWeaponStats CurrentWeaponStats;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Weapon)
	TArray<FNew_WeaponUpgrades_Lvl_Cost> AvailableWeaponUpgrades;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Doors)
	TArray<FNewDoorUpgradesStruct> UpgradeList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Trinket)
	TEnumAsByte<NewTrinketList> EquippedTrinket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Trinket)
	int CurrentTrinketUses;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Trinket)
	FNewMasterTrinketSaveData TrinketSaveStuff;
};
