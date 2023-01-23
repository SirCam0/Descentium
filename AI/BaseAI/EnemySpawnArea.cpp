// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnArea.h"

#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AEnemySpawnArea::AEnemySpawnArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags.Add("SpawnDoor");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorFrameAsset(TEXT("StaticMesh'/Game/CambodianTest/Meshes/NewDoor/RetopFrame.RetopFrame'"));
	UStaticMesh* DoorFrameMesh = DoorFrameAsset.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorAsset(TEXT("StaticMesh'/Game/CambodianTest/Meshes/NewDoor/RetopDoor.RetopDoor'"));
	UStaticMesh* DoorMesh = DoorAsset.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SpawnAreaAsset(TEXT("StaticMesh'/Game/OrganisedContent/AI/SpawnDoors/2/SpawnBoxCollision.SpawnBoxCollision'"));
	UStaticMesh* SpawnAreaMesh = SpawnAreaAsset.Object;

	CentrePoint = CreateDefaultSubobject<USceneComponent>(TEXT("CentrePoint"));
	CentrePoint->SetRelativeLocation(FVector(0));

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(CentrePoint);
	DoorFrame->SetRelativeLocation(FVector(0));
	DoorFrame->SetStaticMesh(DoorFrameMesh);
	RootComponent = CentrePoint;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(CentrePoint);
	Door->SetRelativeLocation(FVector(0));
	Door->SetStaticMesh(DoorMesh);

	SpawnAreaBounds = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnAreaBounds"));
	SpawnAreaBounds->SetupAttachment(CentrePoint);
	SpawnAreaBounds->SetRelativeLocation(FVector(0));
	SpawnAreaBounds->SetStaticMesh(SpawnAreaMesh);

	const float XPosMultiplier = ((SpawnAreaMesh->GetBoundingBox().GetSize().X/3)*-1);
	const float ZPos = (SpawnAreaMesh->GetBoundingBox().GetSize().Z/2)-23;
	const FVector BoxExtent = FVector(XPosMultiplier/2 ,SpawnAreaMesh->GetBoundingBox().GetSize().Y/2, SpawnAreaMesh->GetBoundingBox().GetSize().Z/2);

	SpawnArea1 = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea1"));
	SpawnArea1->SetupAttachment(SpawnAreaBounds);
	SpawnArea1->SetRelativeLocation(FVector(XPosMultiplier*1-(XPosMultiplier*1)/2, 0.f, ZPos));
	SpawnArea1->SetBoxExtent(BoxExtent);
	SpawnArea1->SetCollisionProfileName("AISpawnVolume");
	SpawnArea1->SetCanEverAffectNavigation(false);

	SpawnArea2 = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea2"));
	SpawnArea2->SetupAttachment(SpawnAreaBounds);
	SpawnArea2->SetRelativeLocation(FVector(XPosMultiplier*2-(XPosMultiplier*1)/2, 0.f, ZPos));
	SpawnArea2->SetBoxExtent(BoxExtent);
	SpawnArea2->SetCollisionProfileName("AISpawnVolume");
	SpawnArea2->SetCanEverAffectNavigation(false);

	SpawnArea3 = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea3"));
	SpawnArea3->SetupAttachment(SpawnAreaBounds);
	SpawnArea3->SetRelativeLocation(FVector(XPosMultiplier*3-(XPosMultiplier*1)/2, 0.f, ZPos));
	SpawnArea3->SetBoxExtent(BoxExtent);
	SpawnArea3->SetCollisionProfileName("AISpawnVolume");
	SpawnArea3->SetCanEverAffectNavigation(false);

	Exit = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit"));
	Exit->SetupAttachment(SpawnAreaBounds);
	Exit->SetRelativeLocation(FVector(0.f-(BoxExtent.X/3), 0.f, ZPos));
	Exit->SetBoxExtent(FVector((BoxExtent.X/3),BoxExtent.Y,BoxExtent.Z));
	Exit->SetCollisionProfileName("OverlapAllDynamic");
	Exit->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void AEnemySpawnArea::BeginPlay()
{
	Super::BeginPlay();
	FHitResult Trace1HitResult;
	FHitResult Trace2HitResult;
	FHitResult Trace3HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("TraceVisibility")),false);
	GetWorld()->LineTraceSingleByChannel(Trace1HitResult, SpawnArea1->GetComponentLocation(), SpawnArea1->GetComponentLocation()-FVector(0.f,0.f,700), ECC_Visibility, TraceParams);
	GetWorld()->LineTraceSingleByChannel(Trace2HitResult, SpawnArea2->GetComponentLocation(), SpawnArea2->GetComponentLocation()-FVector(0.f,0.f,700), ECC_Visibility, TraceParams);
	GetWorld()->LineTraceSingleByChannel(Trace3HitResult, SpawnArea3->GetComponentLocation(), SpawnArea3->GetComponentLocation()-FVector(0.f,0.f,700), ECC_Visibility, TraceParams);
	SpawnArea1Loc = Trace1HitResult.ImpactPoint;
	SpawnArea2Loc = Trace2HitResult.ImpactPoint;
	SpawnArea3Loc = Trace3HitResult.ImpactPoint;
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnEnemiesFromQueueTimerHandle, this, &AEnemySpawnArea::SpawnEnemyFromQueue, 0.5,true);
	}
}

void AEnemySpawnArea::SpawnEnemyFromQueue()
{
	if(SpawnQueue.Num() != 0)
	{
		const FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = PickSpawnLocation();
		if(SpawnLocation != FVector(0))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spawning Enemy")));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%s"), *PickSpawnLocation().ToString()));
			if (SpawnQueue[0]->IsValidLowLevelFast())
			{
				//FVector HeightModifier = FVector(0.f,0.f,Cast<ABaseAI>(SpawnQueue[0])->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
				ABaseAI* SpawnedEnemy = GetWorld()->SpawnActor<ABaseAI>(SpawnQueue[0], SpawnLocation/*+FVector(0,0,130)*/,this->GetActorRotation(),SpawnParams);
				if(SpawnedEnemy->IsValidLowLevelFast())
				{
					EnemiesEntered.Add(SpawnedEnemy);
					SpawnedEnemy->GetCapsuleComponent()->SetCollisionProfileName("AISpawned");
					SpawnQueue.RemoveAt(0);
					OpenDoor();
					SpawnedEnemy->WalkForwardFromStartDistance = UKismetMathLibrary::Vector_Distance((this->GetActorForwardVector()*500.f)+this->GetActorLocation(), SpawnedEnemy->GetActorLocation());
					if(Manager->IsValidLowLevelFast())
					{
						SpawnedEnemy->WaveManager = Manager;
						SpawnedEnemy->TempCurrencyToDrop = TempCurrencyPerEnemy;
						SpawnedEnemy->PermaCurrencyToDrop = PermaCurrencyPerEnemy;
						Manager->AliveEnemies.Add(SpawnedEnemy);
					}
				}
			}
		}
	}
}

FVector AEnemySpawnArea::PickSpawnLocation()
{
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(Zone1Empty){
		Zone1Empty = false;
		FNavLocation NavLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(SpawnArea1Loc, 20.f, NavLocation);
		return 	SpawnArea1Loc;;
	}
	else if(Zone2Empty){
		Zone2Empty = false;
		FNavLocation NavLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(SpawnArea2Loc, 20.f, NavLocation);
		return 	NavLocation.Location;;
	}
	else if(Zone3Empty){
		Zone3Empty = false;
		FNavLocation NavLocation;
		NavigationSystem->GetRandomPointInNavigableRadius(SpawnArea3Loc, 20.f, NavLocation);
		return 	NavLocation.Location;;
	}
	else
	{
		return FVector(0);
	}
}

// Called every frame
void AEnemySpawnArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


