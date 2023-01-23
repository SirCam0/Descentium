#pragma once
#include "NewDoorUpgrades.h"
#include "Descentium/SaveRunStructs/Weapon/NewUpgradeLVL.h"
#include "NewDoorUpgradesStruct.generated.h"

USTRUCT(BlueprintType)
struct FNewDoorUpgradesStruct
{

	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewDoorUpgrades> UpgradeType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> UpgradeLVL;
	
};
