// Fill out your copyright notice in the Description page of Project Settings.


#include "MySkremlinAI.h"

#include "ArtificialIntelligenceManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StructsAndEnums/EnemyValueStructs/SkremlinAIValues.h"
#include "Kismet/GameplayStatics.h"


AMySkremlinAI* AMySkremlinAI::GetSkremlinAIREF_Implementation()
{
	return this;
}

void AMySkremlinAI::BeginPlay()
{
	Super::BeginPlay();
	AIManager = Cast<AArtificialIntelligenceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AArtificialIntelligenceManager::StaticClass()));
	if (DataTableBaseValues->IsValidLowLevelFast())
	{
		FName RowName = "SkremlinAI";
		this->Health = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->Health;
		this->MaxHealth = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->Health;
		this->ShieldHP = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->ShieldHP;
		this->ShieldingMaxHP = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->ShieldHP;
		this->GetCharacterMovement()->MaxWalkSpeed = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->WalkSpeed;
		this->DamageAmount = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->DamageAmount;
		this->hierarchy = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->Hierarchy;
		this->CanBeHooked = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->bCanBeHooked;
		this->AmountOfCoinsToSteal = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->CoinsToSteal;
		this->CoinsPerSecondLost = DataTableBaseValues->FindRow<FSkremlinAIValues>(RowName,"")->CoinsPerSecondLost;
		SetShield();
	}
}

void AMySkremlinAI::Death(bool CritDeath)
{
	ReturnCoins(CoinsHeld);
	Super::Death(CritDeath);
}

void AMySkremlinAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMySkremlinAI::PlayAttackAnim()
{
	if(CurrentHeldTokens.Contains(TokenTypeEnum::Melee))
	{
		if(AttackAnim->IsValidLowLevelFast())
		{
			Swinging = true;
			this->GetMesh()->GetAnimInstance()->Montage_Play(AttackAnim);
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("PlayingMontage")));
			//Attacking = false;
		}
	}
}

void AMySkremlinAI::ResetSwinging()
{
	Swinging = false;
}

