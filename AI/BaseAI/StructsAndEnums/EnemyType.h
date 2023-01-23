// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * UEnun template file created by Cameron.Greenway 15/03/22
 */

UENUM()
enum EnemyType
{
	MeleeEnemy UMETA(DisplayName = "Melee"),
	Skremlin UMETA(DisplayName = "Skremlin"),
	Simul UMETA(DisplayName = "Simul"),
	Ranged UMETA(DisplayName = "Ranged"),
	SuicideSpawner UMETA(DIsplayName = "SuicideSpawner"),
	SuicideSeeker UMETA(DisplayName = "SuicideSeeker"),
	OdiumCirrum UMETA(DisplayName = "OdiumCirrum"),
};
