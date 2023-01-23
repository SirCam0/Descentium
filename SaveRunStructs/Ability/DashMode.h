#pragma once


UENUM(BlueprintType)
enum DashModeNew
{
	DefaultDash UMETA(DisplayName = "DefaultDash"),
	ChargeDash UMETA(DisplayName = "ChargeDash"),
	DamageWall UMETA(DisplayName = "DamageWall"),
	ChargeUpAOE UMETA(DisplayName = "ChargeUpAOE"),
	MultiDash UMETA(DisplayName = "MultiDash"),
};