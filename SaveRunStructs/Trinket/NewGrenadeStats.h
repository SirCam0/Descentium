#pragma once
#include "NewGrenadeType.h"
#include "NewGrenadeStats.generated.h"

USTRUCT(BlueprintType)
struct FNewGrenadeStats
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<NewGrenadeType> EquippedGrenadeType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Range;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Min_DMG;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Max_Dmg;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Fuse_Time;
	
};
