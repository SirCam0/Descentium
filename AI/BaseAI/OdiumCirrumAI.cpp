// Fill out your copyright notice in the Description page of Project Settings.


#include "OdiumCirrumAI.h"

#include "NavMeshNode.h"
#include "Kismet/GameplayStatics.h"

AOdiumCirrumAI* AOdiumCirrumAI::GetOdiumCirrumAIREF_Implementation()
{
	return this;
}

void AOdiumCirrumAI::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	NavNode = GetWorld()->SpawnActor<ANavMeshNode>(ANavMeshNode::StaticClass(), this->GetActorLocation(), FRotator(0,0,0),SpawnParams);
	NavNode->Location = this->GetActorLocation();
	NavNode->Grid = Cast<AA3DNavMesh>(UGameplayStatics::GetActorOfClass(this, AA3DNavMesh::StaticClass()));
}

void AOdiumCirrumAI::Death(bool CritDeath)
{
	ClosePortal();
	Super::Death(CritDeath);
}

void AOdiumCirrumAI::Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool bCrit)
{
	float DamageAmount = Damage;
	if(!bCrit)
	{
		DamageAmount = Damage * OuterShellDamageMultiplier;
	}
	Super::Damage(DamageAmount, ImpactPoint, ImpactNormal, bCrit);
}

AOdiumCirrumAI::AOdiumCirrumAI(){
	
	
}
