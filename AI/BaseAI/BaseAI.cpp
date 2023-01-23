// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI.h"

#include "ArtificialIntelligenceManager.h"
#include "NiagaraFunctionLibrary.h"
#include "DamageNumber.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "SpawnDoorsManager.h"
#include "Components/CapsuleComponent.h"
#include "Descentium/RogueLiteGameInstanceParent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABaseAI* ABaseAI::GetMyBaseAIREF_Implementation()
{
	if(this->IsValidLowLevelFast())
	{
		return this;
	}
	else{
		return nullptr;
	}
}

// Sets default values
ABaseAI::ABaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CritSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CritSphere"));
	CritSphere->SetSphereRadius(50.f);
	CritSphere->SetupAttachment(RootComponent);
	CritSphere->ComponentTags.Add("CritZone");
	CritSphere->SetCollisionProfileName("CharacterMesh");

	Tags.Add("NewBaseAI");
	Tags.Add("Enemy");

	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetRelativeLocation(FVector(0,0,GetCapsuleComponent()->GetScaledCapsuleHalfHeight()+50));
	HealthBar->SetRelativeScale3D(FVector(0.3));

	DisolveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DisolveTimeline"));
	DisolveTimelineUpdateFunction.BindUFunction(this, FName("DisolveTimelineFloatReturn"));
	DisolveTimelineFinishedFunction.BindUFunction(this, FName("DisolveTimelineFinished"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveOBJ(TEXT("CurveFloat'/Game/OrganisedContent/C++Blueprints/BaseAIStuff/DisolveCurve.DisolveCurve'"));
	DisolveTimelineCurve = CurveOBJ.Object;
}

// Called when the game starts or when spawned
void ABaseAI::BeginPlay()
{
	Super::BeginPlay();
	AITokenManager = Cast<AArtificialIntelligenceManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AArtificialIntelligenceManager::StaticClass()));
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this,0);
	GameInstance = Cast<URogueLiteGameInstanceParent>(UGameplayStatics::GetGameInstance(this));
	
	if (DisolveTimelineCurve->IsValidLowLevelFast()) {
		DisolveTimeline->AddInterpFloat(DisolveTimelineCurve, DisolveTimelineUpdateFunction, FName("Float"));
		DisolveTimeline->SetTimelineFinishedFunc(DisolveTimelineFinishedFunction);
		DisolveTimeline->SetLooping(false);
		DisolveTimeline->SetIgnoreTimeDilation(false);
	}
}

void ABaseAI::Highlight(bool highlight)
{
	if(!HighlightOveride)
	{
		Highlighting = highlight;
		if(highlight)
		{
			this->GetMesh()->SetRenderCustomDepth(true);
			this->GetMesh()->SetCustomDepthStencilValue(1);
			this->TestMesh->SetRenderCustomDepth(true);
			this->TestMesh->SetCustomDepthStencilValue(1);
		}
		else
		{
			this->GetMesh()->SetRenderCustomDepth(false);
		}
	}
}

void ABaseAI::SetShield()
{
	if(ShieldMaterial->IsValidLowLevelFast())
	{
		if(ShieldHP > 0)
		{
			GetMesh()->SetMaterial(0,ShieldMaterial);
		}
	}
}

void ABaseAI::Death(bool CritDeath)
{
	if(!Dead)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Death"));
		ReturnAllTokens();
		if(WaveManager->IsValidLowLevelFast())
		{
			WaveManager->EnemyDied(this);
			if(NonDoorLocation != nullptr)
			{
				WaveManager->AvailableNonDoorSpawnLocations.Add(NonDoorLocation);
			}
		}
		if(DeathVFX->IsValidLowLevelFast())
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, DeathVFX, this->GetActorLocation(), this->GetActorRotation(), FVector(1));
		}
		if(TempCurrencyBlueprint->IsValidLowLevel())
		{
			if(FMath::RoundHalfFromZero(TempCurrencyToDrop) != 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue, FString::Printf(TEXT("Currency %f"), FMath::RoundHalfFromZero(CurrencyToDrop)));
				for(float i = FMath::RoundHalfFromZero(TempCurrencyToDrop)-1; i >= 0; i--)
				{
					FActorSpawnParameters SpawnInfo;
					SpawnInfo.bNoFail = true;
					GetWorld()->SpawnActor<AActor>(TempCurrencyBlueprint,this->GetActorLocation(),FRotator(0), SpawnInfo);
				}
			}
		}
		if(PermaCurrencyBlueprint->IsValidLowLevel())
		{
			//GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue, FString::Printf(TEXT("Currency %f"), FMath::RoundHalfFromZero(PermaCurrencyToDrop)));
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.bNoFail = true;
			if(FMath::RoundHalfFromZero(PermaCurrencyToDrop) != 0)
			{
				for(float i = FMath::RoundHalfFromZero(PermaCurrencyToDrop)-1; i >= 0; i--)
				{

					GetWorld()->SpawnActor<AActor>(PermaCurrencyBlueprint,this->GetActorLocation(),FRotator(0), SpawnInfo);
				}
			}else
			{
				if(UKismetMathLibrary::RandomFloatInRange(0,1) < PermaCurrencyToDrop)
				{
					GetWorld()->SpawnActor<AActor>(PermaCurrencyBlueprint,this->GetActorLocation(),FRotator(0), SpawnInfo);
				}
			}
		}
	
		if(DisolveOnDeath)
		{
			UpdateRunStats();
			this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			this->GetCapsuleComponent()->SetCollisionProfileName("OverlapAllDynamic");
			this->CritSphere->SetCollisionEnabled((ECollisionEnabled::NoCollision));
			this->HealthBar->SetHiddenInGame(true);
			this->GetCharacterMovement()->DisableMovement();
			this->GetMesh()->SetCollisionProfileName("Ragdoll");
			this->GetMesh()->SetSimulatePhysics(true);
			FVector ImpulseDirection = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(UGameplayStatics::GetPlayerCharacter(this,0)->GetActorLocation(), this->GetActorLocation()));
			//this->GetMesh()->AddImpulseAtLocation(ImpulseDirection*5000,this->GetActorLocation(),this->GetMesh()->GetBoneName(0));
			this->GetMesh()->SetPhysicsLinearVelocity(ImpulseDirection*1000);
			this->GetMesh()->WakeAllRigidBodies();
			Dead = true;
			AwaitingToken = false;
			OnDeath(CritDeath);
			DisolveTimeline->PlayFromStart();
		}
		else
		{
			UpdateRunStats();
			OnDeath(CritDeath);
			Destroy();
		}
	}
}
/**
void ABaseAI::Twitch()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Twitching"));
}

void ABaseAI::Falter()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Faltering"));
	if (this->GetMesh()->GetAnimInstance()->IsValidLowLevelFast())
	{
		ReturnAllTokens();
		this->GetMesh()->GetAnimInstance()->StopAllMontages(0.f);
	}
}

void ABaseAI::Stagger()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, TEXT("Staggering"));
	if (this->GetMesh()->GetAnimInstance()->IsValidLowLevelFast())
	{
		ReturnAllTokens();
		this->GetMesh()->GetAnimInstance()->StopAllMontages(0.f);
		if(StaggerAnim->IsValidLowLevelFast())
		{
			this->GetMesh()->GetAnimInstance()->Montage_Play(StaggerAnim);
		}
	}
}
*/
void ABaseAI::ReturnAllTokens()
{
	int num = 0;
	if(AITokenManager->IsValidLowLevelFast())
	{
		for (auto token : CurrentHeldTokens)
		{
			num++;
			AITokenManager->ReturnToken(token);
		}
		CurrentHeldTokens.Empty();
	}
}

FVector ABaseAI::GetPredictedLocation()
{
	return AITokenManager->PredictedPlayerLocation;
}

void ABaseAI::Damage(int Damage, FVector ImpactPoint, FVector ImpactNormal, bool Crit)
{
	if(DamageSharing)
	{
		for(int index = 0; index < DamageSharedActors.Num(); index++)
		{
			if(DamageSharedActors[index]->IsValidLowLevelFast() && DamageSharedActors[index] != this)
			{
				DamageSharedActors[index]->Damage(Damage, FVector(0), FVector(0), Crit);
			}
		}
	}
	if(Crit)
	{
		Damage *= CritModifier;
		UGameplayStatics::PlaySound2D(this, CritSound, 1, 1, 0);
	}
	if(GameInstance->IsValidLowLevelFast())
	{
		GameInstance->AddTotalDamageBP(Damage);
	}
	if(Damage >= HitReactionThresholds.Twitch)
	{
		Twitch();
	}
	if(ShieldHP > 0)
	{
		ShieldHP -= Damage;
		if(ShieldHP < 0)
		{
			if(BaseMaterial->IsValidLowLevelFast())
			{
				GetMesh()->SetMaterial(0,BaseMaterial);
			}
			Health+=ShieldHP;
		}
	}
	else
	{
		Health -= Damage;
	}
	constexpr int LifetimeUpdate = 1;
	DamageTotal = DamageTotal + Damage;
	ApplyCombo(DamageTotal);
	if(ImpactVFX->IsValidLowLevelFast())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, ImpactPoint, ImpactNormal.Rotation(), FVector(1));
	}
	GetWorld()->GetTimerManager().SetTimer(ApplyDamageTimerHandle, this, &ABaseAI::ResetApplyDamageTimerHandle, LifetimeUpdate, false);
	if(CurrentDamageNumber->IsValidLowLevelFast())
	{
		CurrentDamageNumber->ExtendLifetime(DamageTotal, LifetimeUpdate);
		if(Crit)
		{
			CurrentDamageNumber->PlayCritAnimation();
		}
	}
	else
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.bNoFail = true;
		if(ImpactPoint == FVector(0.f, 0.f, 0.f))
		{
			ImpactPoint = this->GetActorLocation();
		}
		if(DamageNumberBlueprint->IsValidLowLevelFast())
		{
			CurrentDamageNumber = Cast<ADamageNumber>(GetWorld()->SpawnActor<AActor>(DamageNumberBlueprint, ImpactPoint+FVector(100.f,0.f,0.f), ImpactNormal.Rotation(), SpawnInfo));
			if(CurrentDamageNumber->IsValidLowLevelFast())
			{
				CurrentDamageNumber->SetText(DamageTotal);
				if(Crit)
				{
					CurrentDamageNumber->PlayCritAnimation();
				}
				CurrentDamageNumber->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget,EAttachmentRule::KeepRelative,EAttachmentRule::KeepRelative,false),NAME_None);
				CurrentDamageNumber->Owner = this;
			}
		}
	}
	if(Health <= 0)
	{
		Death(Crit);
	}
}

void ABaseAI::DoDamageSharing(TArray<ABaseAI*> Enemies)
{
	DamageSharing = true;
	DamageSharedActors = Enemies;
}

void ABaseAI::StopDamageSharing()
{
	DamageSharing = false;
}

void ABaseAI::ResetApplyDamageTimerHandle()
{
	DamageTotal = 0;
	ApplyDamageTimerHandle.Invalidate();
	ResetCombo();
}

void ABaseAI::ApplyCombo(int Damage)
{
	if(Damage > HitReactionThresholds.Stagger)
	{
		if(!StaggerDoOnce)
		{
			if(UKismetMathLibrary::RandomInteger64InRange(0,4) == 1)
			{
				StaggerDoOnce = true;
				Stagger();
			}
		}
	}
	else if(Damage > HitReactionThresholds.Falter)
	{
		if(!FalterDoOnce)
		{
			if(UKismetMathLibrary::RandomInteger64InRange(0,2) == 1)
			{
				FalterDoOnce = true;
				Falter();
			}
		}
	}
}

void ABaseAI::ResetCombo()
{
	StaggerDoOnce = false;
	FalterDoOnce = false;
}

// Called every frame
void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(PlayerCharacter->IsValidLowLevelFast())
	{
		HealthBar->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(HealthBar->GetComponentToWorld().GetLocation(),PlayerCharacter->GetActorLocation()));
	}
}

// Called to bind functionality to input
void ABaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseAI::Stunned(float Duration)
{
	bStunned = true;
	this->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetWorld()->GetTimerManager().SetTimer(StunnedTimerHandle, this, &ABaseAI::StunnedTimerComplete, Duration, false);
}

void ABaseAI::TimeDilate(float Duration, float Dilation)
{
	
}

void ABaseAI::DisolveTimelineFloatReturn(float value)
{
	this->GetMesh()->SetScalarParameterValueOnMaterials("Amount", value);
}

void ABaseAI::DisolveTimelineFinished()
{
	Destroy();
}


void ABaseAI::StunnedTimerComplete()
{
	this->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	bStunned = false;
}

void ABaseAI::Bleed(float BleedPulseInterval, float NumberOfIntervals, int DamagePerInterval, FVector HitLocation, FVector HitNormal)
{
	BleedCount = NumberOfIntervals;
	BleedInterval = BleedPulseInterval;
	BleedDamage = DamagePerInterval;
	BleedingRelativeLocation = HitLocation - this->GetActorLocation();
	GetWorld()->GetTimerManager().SetTimer(BleedTimerHandle, BleedPulseInterval, true);
	if(!CurrentBleedVFX)
	{
		CurrentBleedVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(BleedVFX, RootComponent, "none", HitLocation, HitNormal.Rotation(), static_cast<EAttachLocation::Type>(EAttachmentRule::SnapToTarget), false, true);
	}
}

void ABaseAI::BleedTimerInterval()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, FString::Printf(TEXT("Damaging")));
	BleedCount -= BleedInterval;
	Damage(BleedDamage, this->GetActorLocation() + BleedingRelativeLocation, FVector(0), false);
	if(BleedCount <= 0)
	{
		BleedTimerHandle.Invalidate();
		if(!CurrentBleedVFX)
		{
			CurrentBleedVFX->DestroyInstance();
		}
	}
}

void ABaseAI::SetSpeed(float Duration, float SpeedPercentage)
{
	SpeedModifier = SpeedPercentage / 100.f;
	if(!Slowed)
	{
		Slowed = true;
		MaxWalkSpeedTemp = this->GetCharacterMovement()->MaxWalkSpeed;
	}
	this->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedTemp * SpeedModifier;
	GetWorld()->GetTimerManager().SetTimer(SetSpeedTimerHandle, this, &ABaseAI::SetSpeedTimerComplete, Duration, false);
}

void ABaseAI::SetSpeedTimerComplete()
{
	Slowed = false;
	SpeedModifier = 1.f;
	this->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeedTemp;
}

void ABaseAI::SmartJump(FVector StartLocation, FVector EndLocation, FVector EndLocationVelocity)
{
	const float HeightDifference = EndLocation.Z - StartLocation.Z;
	const float Duration = UKismetMathLibrary::MapRangeClamped(HeightDifference, 2000.f, 0.f, 2.5,0);
	const FVector Temp = StartLocation - EndLocation;
	const float Distance = sqrt((Temp.X*Temp.X) + (Temp.Y*Temp.Y) + (Temp.Z*Temp.Z));
	const FVector Vector1 = (EndLocationVelocity*(Distance/2000.f))+EndLocation;
	const float X = (Vector1.X - StartLocation.X)/Duration;
	const float Y = (Vector1.Y - StartLocation.Y)/Duration;
	const float Z = (Vector1.Z - StartLocation.Z+(((Duration*Duration)*-0.5f)*982.f))/Duration;
	this->LaunchCharacter(FVector(X,Y,Z), true, true);
}

void ABaseAI::ReceiveToken(TokenTypeEnum TokenType, float HoldForDuration)
{
	CurrentHeldTokens.Add(TokenType);
	LastReceivedToken = TokenType;
	//GetWorld()->GetTimerManager().SetTimer(TokenUseTimerHandle, this, &ABaseAI::ReturnTokenAfterTimer, HoldForDuration, false);
}

void ABaseAI::ReturnTokenAfterTimer()
{
	int TokenIndex = -1;
	int index = 0;
	for (auto Token : CurrentHeldTokens)
	{
		if(Token==LastReceivedToken)
		{
			TokenIndex = index;
		}
		index++;
	}
	if(TokenIndex != -1)
	{
		this->CurrentHeldTokens.RemoveAt(TokenIndex);
	}
	if(AITokenManager->IsValidLowLevelFast())
	{
		AITokenManager->ReturnToken(LastReceivedToken);
	}
}
