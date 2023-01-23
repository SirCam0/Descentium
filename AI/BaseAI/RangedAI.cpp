// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedAI.h"
#include "ArtificialIntelligenceManager.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ARangedAI::ARangedAI()
{

}

void ARangedAI::BeginPlay()
{
	Super::BeginPlay();

	if (DataTableBaseValues->IsValidLowLevelFast())
	{
		FName RowName = "RangedAI";
		this->Health = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->Health;
		this->MaxHealth = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->Health;
		this->ShieldHP = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->ShieldHP;
		this->ShieldingMaxHP = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->ShieldHP;
		this->CanBeHooked = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->bCanBeHooked;
		this->hierarchy = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->Hierarchy;
		this->AccuracyDistributionCurve = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->AccuracyCurve;
		this->GetCharacterMovement()->MaxWalkSpeed = DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->WalkSpeed;
		SetShield();
	}
	//FireBullet();
}

void ARangedAI::PlayAttackAnim()
{
	if(CurrentHeldTokens.Contains(TokenTypeEnum::Projectile))
	{
		if(ChargeShotAnim->IsValidLowLevelFast())
		{
			TokenUseTimerHandle.Invalidate();
			if (DataTableBaseValues->IsValidLowLevelFast())
			{
				FName RowName = "RangedAI";
				this->GetMesh()->GetAnimInstance()->Montage_Play(ChargeShotAnim, DataTableBaseValues->FindRow<FRangedAIValues>(RowName,"")->AttackSpeed_Anim);
			}
			else
			{
				this->GetMesh()->GetAnimInstance()->Montage_Play(ChargeShotAnim);
			}
		}
		if (ChargeShotVFX->IsValidLowLevelFast())
		{
			UNiagaraFunctionLibrary::SpawnSystemAttached(ChargeShotVFX, this->GetMesh(), TEXT("Ranged_ChargeUp_Socket"), FVector(0), FRotator(0), EAttachLocation::SnapToTarget, true, true);
		}
	}
}

void ARangedAI::FireBullet()
{
	if(PlayerCharacter->IsValidLowLevelFast() && !Dead)
	{
		float total = 0;
		for (float i = 0.f; i <= 1.f; i+= 0.1f)
		{
			if  (AccuracyDistributionCurve->IsValidLowLevelFast())
			{
				total += AccuracyDistributionCurve->GetFloatValue(i);
			}
		}
		const float FirstPass = FMath::FRandRange(0,total);
		float section = 0;
		float iteration = 0;
		for (float i = 0.f; i <= 1.f; i+= 0.1f)
		{
			if(AccuracyDistributionCurve->IsValidLowLevelFast())
			{
				iteration += AccuracyDistributionCurve->GetFloatValue(i);
				if(iteration < FirstPass)
				{
					section = i;
				}
			}
		}
		const float SecondPass = FMath::FRandRange(section,section+0.1);
		const float AccuracyModifierFirstPass = FMath::GetMappedRangeValueClamped(FVector2D(0,1),FVector2D(0,AccuracyDistanceRangeMax),SecondPass);
		FVector PlayerVelocity;
		if(AITokenManager->IsValidLowLevelFast())
		{
			PlayerVelocity = AITokenManager->GetPredictedPlayerVelocity();
		}
		else
		{
			PlayerVelocity = PlayerCharacter->GetVelocity();
		}
		float AccuracyModifier = FMath::GetMappedRangeValueClamped(FVector2D(0,1400), FVector2D(0,AccuracyModifierFirstPass), PlayerVelocity.Size());
		if(!FMath::RandBool())
		{
			AccuracyModifier *= -1;
		}
		const float Distance = (this->GetActorLocation() - (PlayerCharacter->GetActorLocation()+FVector(0.f,0.f,15.f))).Size();
		const FRotator Temp = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation(TEXT("Ranged_ChargeUp_Socket")), PlayerCharacter->GetActorLocation());
		const FVector EndLocation = (PlayerCharacter->GetActorLocation() + PlayerCameraOffset)+ UKismetMathLibrary::GetRightVector(Temp) * AccuracyModifier;
		const FVector EndPositionCalculated = EndLocation+(PlayerVelocity * Distance / ProjectileSpeed);
		const FRotator ProjectileRotation = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetSocketLocation(TEXT("Ranged_ChargeUp_Socket")), EndPositionCalculated);
		const FVector ProjectileVelocity = FVector(UKismetMathLibrary::GetForwardVector(ProjectileRotation)*ProjectileSpeed);
		SpawnProjectile(GetMesh()->GetSocketLocation(TEXT("Ranged_ChargeUp_Socket")), ProjectileRotation, ProjectileVelocity, EndPositionCalculated);
		AITokenManager->ReturnToken(TokenTypeEnum::Projectile);
		int TokenIndex = -1;
		int index = 0;
		for (auto Token : CurrentHeldTokens)
		{
			if(Token==TokenTypeEnum::Projectile)
			{
				TokenIndex = index;
			}
			index++;
		}
		if(TokenIndex != -1)
		{
			this->CurrentHeldTokens.RemoveAt(TokenIndex);
		}
	}
}

//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f"), AccururacyModifier));
//GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Hello %s"),*ProjectileRotation.ToString()));