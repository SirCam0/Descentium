// Fill out your copyright notice in the Description page of Project Settings.


#include "SuicideSpawnerAI.h"

#include "NiagaraFunctionLibrary.h"
#include "SpawnDoorsManager.h"
#include "SuicideAI.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASuicideSpawnerAI* ASuicideSpawnerAI::GetSpawnerAIREF_Implementation()
{
	return this;
}

ASuicideSpawnerAI::ASuicideSpawnerAI()
{
	ProximityCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProximityCollider"));
	ProximityCollisionSphere->SetupAttachment(RootComponent);
	ProximityCollisionSphere->SetSphereRadius(CollisionSphereRadius);
	ProximityCollisionSphere->SetCollisionProfileName("OverlapOnlyPlayer");
	ProximityCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASuicideSpawnerAI::ProximityBeginOverlap);
}

void ASuicideSpawnerAI::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemyLoop();
	FActorSpawnParameters SpawnParams;
	FVector location = UKismetMathLibrary::GetUpVector(this->GetActorRotation())*300+this->GetActorLocation();
	GetWorld()->SpawnActor<ANavMeshNode>(ANavMeshNode::StaticClass(),location,FRotator(0),SpawnParams);
	ExitNode = GetWorld()->SpawnActor<ANavMeshNode>(ANavMeshNode::StaticClass(),location,FRotator(0),SpawnParams);
	ExitNode->Grid = Cast<AA3DNavMesh>(UGameplayStatics::GetActorOfClass(this, AA3DNavMesh::StaticClass()));
	ExitNode->Location = location;
}

void ASuicideSpawnerAI::SpawnEnemyLoop()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyLoopTimerHandle, this, &ASuicideSpawnerAI::PlaySpawnAnimation, SpawnInterval+UKismetMathLibrary::RandomFloatInRange(-1.5,1.5), false);
}

void ASuicideSpawnerAI::PlaySpawnAnimation()
{
	if(SpawnedEnemies.Num() <= MaxSuicideEnemies)
	{
		//this->GetMesh()->GetAnimInstance()->Montage_Play(SpawnAnim);
		Spawning = true;
	}
}

void ASuicideSpawnerAI::SpawnEnemy()
{
	if(!Dead)
	{
		if(SpawnedEnemies.Num() - 1 <= MaxSuicideEnemies)
		{
			const FActorSpawnParameters SpawnParams;
			const FVector SpawnLocation = this->GetMesh()->GetSocketLocation("SpawnPoint");
			//const FRotator PlayerLookARotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerLocation);
			//const FRotator SpawnRotation = FVector(0,0,PlayerLookARotator.Yaw).Rotation();
			if(SuicideEnemy->IsValidLowLevelFast())
			{
				ABaseAI* SpawnedEnemy = GetWorld()->SpawnActor<ABaseAI>(SuicideEnemy, SpawnLocation + FVector(0,0, 0), this->GetActorRotation(), SpawnParams);
				if(SpawnedEnemy->IsValidLowLevelFast())
				{
					SpawnEnemyLoop();
					ASuicideAI* Enemy = Cast<ASuicideAI>(SpawnedEnemy);
					Enemy->Spawner = this;
					Enemy->FirstNode = ExitNode;
					SpawnedEnemies.Add(SpawnedEnemy);
					if(SpurtVFX->IsValidLowLevelFast())
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SpurtVFX, SpawnLocation, this->GetActorRotation(), FVector(1));
					}
					if(WaveManager->IsValidLowLevelFast())
					{
						if(WaveManager->Highlighting)
						{
							SpawnedEnemy->GetMesh()->SetRenderCustomDepth(true);
							SpawnedEnemy->GetMesh()->SetCustomDepthStencilValue(1);
						}
						WaveManager->UpdateEnemiesLeft();
						SpawnedEnemy->WaveManager = WaveManager;
						WaveManager->AliveEnemies.Add(SpawnedEnemy);
					}
				}
			}
		}
	}
}

void ASuicideSpawnerAI::EnemyKilled(ABaseAI* KilledEnemy)
{
	if(KilledEnemy != nullptr)
	{
		int Index = 0;
		int IndexToRemoveThis = -1;
		for (ABaseAI* Enemy : SpawnedEnemies)
		{
			if (Enemy == KilledEnemy)
			{
				IndexToRemoveThis = Index;
			}
			Index++;
		}
		if(IndexToRemoveThis != -1)
		{
			SpawnedEnemies.RemoveAt(IndexToRemoveThis);
		}
	}
}

void ASuicideSpawnerAI::ProximityBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		FHitResult hit;
		FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), false, this);
		GetWorld()->LineTraceSingleByChannel(hit, this->GetActorLocation(), OtherActor->GetActorLocation(),ECC_Visibility, TraceParams);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Entered Proximity")));
		if(!hit.bBlockingHit)
		{
			if(ProximityVFX->IsValidLowLevelFast())
			{
				DamagePlayer();
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ProximityVFX, this->GetActorLocation(), this->GetActorRotation(), FVector(1));
			}
		}
	}
}
