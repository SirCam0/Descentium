// Fill out your copyright notice in the Description page of Project Settings.


#include "GOLAspectOfProtection.h"

void AGOLAspectOfProtection::Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool bCrit)
{
	if(this->Health <= this->MaxHealth/2 && !DoOnce)
	{
		DoOnce = true;
		HalfHealth();
	}
	Super::Damage(Damage, ImpactPoint, ImpactNormal, bCrit);
}
