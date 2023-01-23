// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnDoorsManager.h"
#include "EnemySpawnArea.h"
#include "ScenarioManager.h"
#include "Descentium/RogueLiteGameInstanceParent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnDoorsManager::ASpawnDoorsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnDoorsManager::AddHighlightToAllEnemeies()
{
	for(ABaseAI* Enemy: AliveEnemies)
	{
		if(Enemy->IsValidLowLevelFast())
		{
			Enemy->Highlight(true);
		}
	}
}

void ASpawnDoorsManager::RemoveHighlightFromAllEnemeies()
{
	for(ABaseAI* Enemy: AliveEnemies)
	{
		if(Enemy->IsValidLowLevelFast())
		{
			Enemy->Highlight(false);
		}
	}
}

void ASpawnDoorsManager::ToggleHighlight()
{
	if(HighlightToggle)
	{
		AddHighlightToAllEnemeies();
	}
	else
	{
		RemoveHighlightFromAllEnemeies();
	}
	HighlightToggle = !HighlightToggle;
}

// Called when the game starts or when spawned
void ASpawnDoorsManager::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(this, ANavMeshNode::StaticClass(), AllNavNodesActor);
	if(AllNavNodesActor.Num() != 0)
	{
		for (AActor* Node : AllNavNodesActor)
		{
				AllNavNodes.Add(INavMeshNodeInterface::Execute_GetNavMeshNodeREF(Node));
		}
	}
}

void ASpawnDoorsManager::StartSpawning()
{
	GetWorld()->GetTimerManager().SetTimer(InitialDelayHandle, this, &ASpawnDoorsManager::AfterDelay, InitialDelay, false);
}

void ASpawnDoorsManager::AfterDelay()
{
	URogueLiteGameInstanceParent* GameInstance = Cast<URogueLiteGameInstanceParent>(UGameplayStatics::GetGameInstance(this));
	if(GameInstance->IsValidLowLevelFast())
	{
		if(this->StageNumber == Stage1)
		{
			Scenario = GameInstance->GetStage1Scenario();
		}
		if(this->StageNumber == Stage2)
		{
			Scenario = GameInstance->GetStage2Scenario();
		}
		int TotalEnemies = 0;
		if (Scenario.Waves.Num() != 0)
		{
			for(FWave Wave: Scenario.Waves)
			{
				for(int index = 0; index < Wave.Enemies.Num(); index ++)
				{
					TotalEnemies += Wave.Enemies[index].Number;
				}
			}
			TempCurrencyPerEnemy = Scenario.TempCurrencyDropAmount / TotalEnemies;
			PermaCurrencyPerEnemy = Scenario.PermaCurrencyDropAmount / TotalEnemies;
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Green, FString::Printf(TEXT("Starting room")));
			StartRoom();
		}
	}
}

// Called every frame
void ASpawnDoorsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnDoorsManager::StartRoom()
{
	SpawnNextWave();
}

void ASpawnDoorsManager::SpawnNextWave()
{
	ChangeMusicStartOfWave();
	GetWorld()->GetTimerManager().SetTimer(HighlightAfterTime, this, &ASpawnDoorsManager::ToggleHighlight, 1, true, 20);
	HideEnemiesLeftUI();
	if(Scenario.Waves.Num() - 1 >= CurrentWave)
	{
		ChangeMusicStartOfWave();
		Highlighting = false;
		RemoveHighlightFromAllEnemeies();
		for (FEnemy Enemy :Scenario.Waves[CurrentWave].Enemies)
		{
			for (int i = 0; i < Enemy.Number; i++)
			{
				if(Enemy.Enemy == EnemyType::Ranged)
				{
					AEnemySpawnArea* Door = PickDoor();
					if(Door->IsValidLowLevelFast())
					{
						Door->TempCurrencyPerEnemy = TempCurrencyPerEnemy;
						Door->PermaCurrencyPerEnemy = PermaCurrencyPerEnemy;
						Door->SpawnQueue.Add(RangedEnemyClass);
					}
				}
				if(Enemy.Enemy == EnemyType::Simul)
				{
					AEnemySpawnArea* Door = PickDoor();
					if(Door->IsValidLowLevelFast())
					{
						Door->TempCurrencyPerEnemy = TempCurrencyPerEnemy;
						Door->PermaCurrencyPerEnemy = PermaCurrencyPerEnemy;
						Door->SpawnQueue.Add(SimulEnemyClass);
					}
				}
				if(Enemy.Enemy == EnemyType::Skremlin)
				{
					AEnemySpawnArea* Door = PickDoor();
					if(Door->IsValidLowLevelFast())
					{
						Door->TempCurrencyPerEnemy = TempCurrencyPerEnemy;
						Door->PermaCurrencyPerEnemy = PermaCurrencyPerEnemy;
						Door->SpawnQueue.Add(SkremlinEnemyClass);
					}
				}
				if(Enemy.Enemy == EnemyType::MeleeEnemy)
				{
					AEnemySpawnArea* Door = PickDoor();
					if(Door->IsValidLowLevelFast())
					{
						Door->TempCurrencyPerEnemy = TempCurrencyPerEnemy;
						Door->PermaCurrencyPerEnemy = PermaCurrencyPerEnemy;
						Door->SpawnQueue.Add(MeleeEnemyClass);
					}
				}
				if(Enemy.Enemy == EnemyType::OdiumCirrum)
				{
					FTransform TracedLocation;
					FTransform NonTracedLocation;
					ANonDoorSpawnLocation* NonDoorLocation;
					PickLocation(NonTracedLocation,TracedLocation,NonDoorLocation);
					if(AvailableNonDoorSpawnLocations.IsValidIndex(0))
					{
						AvailableNonDoorSpawnLocations.RemoveAt(0);
					}
					if(NonTracedLocation.GetLocation() != FVector(0))
					{
						UsedLocationsThisWave.Add(NonTracedLocation);
						const FActorSpawnParameters SpawnParams;
						ABaseAI* SpawnedEnemy = GetWorld()->SpawnActor<ABaseAI>(OdiumCirumEnemyClass, NonTracedLocation.GetLocation(),FRotator(0),SpawnParams);
						if(SpawnedEnemy->IsValidLowLevelFast())
						{
							SpawnedEnemy->NonDoorLocation = NonDoorLocation;
							SpawnedEnemy->WaveManager = this;
							SpawnedEnemy->TempCurrencyToDrop = TempCurrencyPerEnemy;
							SpawnedEnemy->PermaCurrencyToDrop = PermaCurrencyPerEnemy;
							this->AliveEnemies.Add(SpawnedEnemy);
						}
					}
				}
				if(Enemy.Enemy == EnemyType::SuicideSeeker)
				{
					AEnemySpawnArea* Door = PickDoor();
					if(Door->IsValidLowLevelFast())
					{
						Door->TempCurrencyPerEnemy = TempCurrencyPerEnemy;
						Door->PermaCurrencyPerEnemy = PermaCurrencyPerEnemy;
						Door->SpawnQueue.Add(SuicideEnemyClass);
					}
				}
				if(Enemy.Enemy == EnemyType::SuicideSpawner)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Spawning"));
					FTransform TracedLocation;
					FTransform NonTracedLocation;
					ANonDoorSpawnLocation* NonDoorLocation;
					PickLocation(NonTracedLocation,TracedLocation, NonDoorLocation);
					if(AvailableNonDoorSpawnLocations.IsValidIndex(0))
					{
						AvailableNonDoorSpawnLocations.RemoveAt(0);
					}
					if(NonTracedLocation.GetLocation() != FVector(0))
					{
						const FActorSpawnParameters SpawnParams;
						if(SuicideSpawnerClass->IsValidLowLevelFast())
						{
							//UKismetSystemLibrary::DrawDebugPoint(this, TracedLocation.GetLocation(), 10, FLinearColor::Red, 10);
							ABaseAI* SpawnedEnemy = GetWorld()->SpawnActor<ABaseAI>(SuicideSpawnerClass, TracedLocation.GetLocation(),TracedLocation.Rotator(),SpawnParams);
							if(SpawnedEnemy->IsValidLowLevelFast())
							{
								SpawnedEnemy->NonDoorLocation = NonDoorLocation;
								SpawnedEnemy->WaveManager = this;
								SpawnedEnemy->TempCurrencyToDrop = TempCurrencyPerEnemy;
								SpawnedEnemy->PermaCurrencyToDrop = PermaCurrencyPerEnemy;
								this->AliveEnemies.Add(SpawnedEnemy);
							}
						}
					}
				}
				UpdateEnemiesLeft();
			}
		}
	}
	CurrentWave++;
}

void ASpawnDoorsManager::EnemyDied(ABaseAI* EnemyToKill)
{
	int Index = 0;
	int KillIndex = -1;
	bool failed = false;
	if(AliveEnemies.Num() != 0)
	{
		for (ABaseAI* Enemy : AliveEnemies)
		{
			if(EnemyToKill->IsValidLowLevelFast() && Enemy->IsValidLowLevelFast())
			{
				if(EnemyToKill == Enemy)
				{
					KillIndex = Index;
				}
				Index++;
			}
			else
			{
				failed = true;
			}
		}
		if(KillIndex != -1)
		{
			if (AliveEnemies.IsValidIndex(KillIndex))
			{
				AliveEnemies.RemoveAt(KillIndex);
			}
		}
		if(failed)
		{
			Index = 0;
			KillIndex = -1;
			for (ABaseAI* Enemy : AliveEnemies)
			{
				if(!Enemy->IsValidLowLevelFast())
				{
					KillIndex = Index;
				}
				Index++;
			}
			if(KillIndex != -1)
			{
				if (AliveEnemies.IsValidIndex(KillIndex))
				{
					AliveEnemies.RemoveAt(KillIndex);
				}
			}
		}
		int EnemiesLeft = 0;
		int TotalScore = 0;
		UpdateEnemiesLeft(EnemiesLeft, TotalScore);
		SetEnemiesLeftUI(EnemiesLeft);
		if(EnemiesLeft <= 5 && CurrentWave == Scenario.Waves.Num())
		{
			Highlighting = true;
			HighlightAfterTime.Invalidate();
			AddHighlightToAllEnemeies();
			ShowEnemiesLeftUI();
		}
		if(EnemiesLeft == 0)
		{
			AliveEnemies.Empty();
		}
		if(TotalScore <= NextWaveHierarchyThreshhold)
		{
			if(Scenario.Waves.Num() - 1 >= CurrentWave)
			{
				SpawnNextWave();
			}
			else if(EnemiesLeft <= 0)
			{
				HideEnemiesLeftUI();
				RoomCleared();
			}
		}
	}
	GetWorld()->GetTimerManager().SetTimer(CheckEnemiesLeftTimer, this, &ASpawnDoorsManager::UpdateEnemiesLeftOnInterval, 2.5,true);
}

void ASpawnDoorsManager::UpdateEnemiesLeft(int &EnemiesLeftPtr, int &TotalScorePtr)
{
	int TotalScore = 0;
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseAI::StaticClass(), Enemies);
	const int EnemiesLeft = Enemies.Num() -1; // needs to be minus one as this function is called before the enemy is destroyed
	for (AActor* Enemy : Enemies)
	{
		if(Enemy->IsValidLowLevelFast())
		{
			if(Enemy->Implements<UMyBaseAIInterface>())
			{
				TotalScore += IMyBaseAIInterface::Execute_GetMyBaseAIREF(Enemy)->hierarchy;
			}
		}
	}
	SetEnemiesLeftUI(EnemiesLeft);
	EnemiesLeftPtr = EnemiesLeft;
	TotalScorePtr = TotalScore;
}

void ASpawnDoorsManager::UpdateEnemiesLeft()
{
	int TotalScore = 0;
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseAI::StaticClass(), Enemies);
	const int EnemiesLeft = Enemies.Num();
	for (AActor* Enemy : Enemies)
	{
		if(Enemy->IsValidLowLevelFast())
		{
			if(Enemy->Implements<UMyBaseAIInterface>())
			{
				TotalScore += IMyBaseAIInterface::Execute_GetMyBaseAIREF(Enemy)->hierarchy;
			}
		}
	}
	SetEnemiesLeftUI(EnemiesLeft);
}

void ASpawnDoorsManager::UpdateEnemiesLeftOnInterval()
{
	int TotalScore = 0;
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ABaseAI::StaticClass(), Enemies);
	const int EnemiesLeft = Enemies.Num();
	for (AActor* Enemy : Enemies)
	{
		if(Enemy->IsValidLowLevelFast())
		{
			if(Enemy->Implements<UMyBaseAIInterface>())
			{
				TotalScore += IMyBaseAIInterface::Execute_GetMyBaseAIREF(Enemy)->hierarchy;
			}
		}
	}
	if(EnemiesLeft <= 0)
	{
		CheckEnemiesLeftTimer.Invalidate();
		HideEnemiesLeftUI();
		RoomCleared();
	}
	SetEnemiesLeftUI(EnemiesLeft);
}

void ASpawnDoorsManager::RoomCleared()
{
	//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Yellow, FString::Printf(TEXT("RoomCleared")));
	HighlightAfterTime.Invalidate();
	HideEnemiesLeftUI();
	OpenPortal();
}

