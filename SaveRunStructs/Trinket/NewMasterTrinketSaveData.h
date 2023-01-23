#pragma once
#include "NewGPSaveStruct.h"
#include "NewGrenadeSaveStruct.h"
#include "NewHPPotSaveStruct.h"
#include "NewShieldSaveStruct.h"
#include "NewMasterTrinketSaveData.generated.h"

USTRUCT(BlueprintType)
struct FNewMasterTrinketSaveData
{
	
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FNewGrenadeSaveStruct GrenadeSaveStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FNewHPPotSaveStruct HPPotSaveStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FNewGPSaveStruct GPSaveStruct;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FNewShieldSaveStruct ShieldSaveStruct;
	
};
