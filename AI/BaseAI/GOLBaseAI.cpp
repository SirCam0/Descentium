// Fill out your copyright notice in the Description page of Project Settings.


#include "GOLBaseAI.h"

void AGOLBaseAI::Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool bCrit)
{
	if(ShieldUp)
	{
		ShieldHealth -= Damage;
		if(ShieldHealth <= 0)
		{
			ShieldUp = false;
			ShieldHealth = ShieldHealthMax;
		}
	}
	else
	{
		Super::Damage(Damage, ImpactPoint, ImpactNormal, bCrit);
	}
}

void AGOLBaseAI::BeginPlay()
{
	Super::BeginPlay();
	ShieldHealth = ShieldHealthMax;
}

void AGOLBaseAI::ResetShield()
{
	ShieldHealth = ShieldHealthMax;
	ShieldUp = false;
}

void AGOLBaseAI::EnableShield()
{
	ShieldHealth = ShieldHealthMax;
	ShieldUp = true;
}