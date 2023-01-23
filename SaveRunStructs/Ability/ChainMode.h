// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/**
 * 
 */
UENUM(BlueprintType)
enum ChainMode
{
 DefaultChain UMETA(DisplayName = "DefaultChain"),
 LifeSap UMETA(DisplayName = "LifeSapChain"),
 MultiWhip UMETA(DisplayName = "MultiWhipChain"),
 DamageShare UMETA(DisplayName = "DamageShareChain"),
};
