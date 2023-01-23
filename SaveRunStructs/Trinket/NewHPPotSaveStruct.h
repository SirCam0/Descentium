#pragma once
#include "Descentium/SaveRunStructs/Weapon/NewUpgradeLVL.h"
#include "NewHPPotSaveStruct.generated.h"

USTRUCT(BlueprintType)
struct FNewHPPotSaveStruct
{
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Unlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> CapacityLVL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> StrengthLVL;
	
};
