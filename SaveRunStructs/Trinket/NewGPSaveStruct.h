#pragma once
#include "Descentium/SaveRunStructs/Weapon/NewUpgradeLVL.h"
#include "NewGPSaveStruct.generated.h"

USTRUCT(BlueprintType)
struct FNewGPSaveStruct
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Unlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool AftershockUnlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool AftershockEquiped;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ForwardShockUnlocked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ForwardShockEquipped;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewUpgradeLVL> DMGLVL;
	
};
