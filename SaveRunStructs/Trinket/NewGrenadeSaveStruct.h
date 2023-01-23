#pragma once
#include "NewGrenadeType.h"
#include "Descentium/SaveRunStructs/Weapon/NewUpgradeLVL.h"
#include "NewGrenadeSaveStruct.generated.h"

USTRUCT(BlueprintType)
struct FNewGrenadeSaveStruct
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Unlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ClusterGrenadeUnlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool StunGrenadeUnlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Time_DialGrenadeUnlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> CapacityLVL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> DMGLVL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewGrenadeType> EquippedGrenadeType;
	
};
