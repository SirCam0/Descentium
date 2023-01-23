// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAI.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "StructsAndEnums/EnemyValueStructs/MeleeAIValues.h"

AMeleeAI::AMeleeAI()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMeleeAI::BeginPlay()
{
	Super::BeginPlay();
	if (DataTableBaseValues->IsValidLowLevelFast())
	{
		FName RowName = "MeleeAI";
		this->Health = DataTableBaseValues->FindRow<FMeleeAIValues>(RowName,"")->Health;
		this->MaxHealth = DataTableBaseValues->FindRow<FMeleeAIValues>(RowName,"")->Health;
		this->ShieldHP = DataTableBaseValues->FindRow<FMeleeAIValues>(RowName,"")->ShieldHP;
		this->ShieldingMaxHP = DataTableBaseValues->FindRow<FMeleeAIValues>(RowName,"")->ShieldHP;
		this->GetCharacterMovement()->MaxWalkSpeed = DataTableBaseValues->FindRow<FMeleeAIValues>(RowName,"")->WalkSpeed;
		this->GetCharacterMovement()->MaxStepHeight = 90;
		SetShield();
	}
}

void AMeleeAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

