// Fill out your copyright notice in the Description page of Project Settings.


#include "GOLAspectOfMind.h"

void AGOLAspectOfMind::Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool bCrit)
{
	StopChargeUp();
	if(bCrit)
	{
		CurrentChargeUpTotal += Damage*CritModifier;
	}
	else
	{
		CurrentChargeUpTotal += Damage;
	}
	Super::Damage(Damage, ImpactPoint, ImpactNormal, bCrit);
}
