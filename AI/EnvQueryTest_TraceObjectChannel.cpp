// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryTest_TraceObjectChannel.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"


#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UEnvQueryTest_TraceObjectChannel::UEnvQueryTest_TraceObjectChannel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Cost = EEnvTestCost::High;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	SetWorkOnFloatValues(false);
	
	Context = UEnvQueryContext_Querier::StaticClass();
}

void UEnvQueryTest_TraceObjectChannel::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	TraceFromContext.BindData(DataOwner, QueryInstance.QueryID);
	ItemHeightOffset.BindData(DataOwner, QueryInstance.QueryID);
	ContextHeightOffset.BindData(DataOwner, QueryInstance.QueryID);

	bool bWantsHit = BoolValue.GetValue();
	bool bTraceToItem = TraceFromContext.GetValue();
	float ItemZ = ItemHeightOffset.GetValue();
	float ContextZ = ContextHeightOffset.GetValue();

	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(Context, ContextLocations))
	{
		return;
	}

	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(EnvQueryTrace), bTraceComplex);

	TArray<AActor*> IgnoredActors;
	if (QueryInstance.PrepareContext(Context, IgnoredActors))
	{
		TraceParams.AddIgnoredActors(IgnoredActors);
	}
	FRunTraceSignature TraceFunc;
	TraceFunc.BindUObject(const_cast<UEnvQueryTest_TraceObjectChannel*>(this), bTraceToItem ? &UEnvQueryTest_TraceObjectChannel::RunLineTraceTo : &UEnvQueryTest_TraceObjectChannel::RunLineTraceFrom);

	for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
	{
		ContextLocations[ContextIndex].Z += ContextZ;
	}

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex()) + FVector(0, 0, ItemZ);
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
		{
			const bool bHit = TraceFunc.Execute(ItemLocation, ContextLocations[ContextIndex], ItemActor, QueryInstance.World, TraceType, TraceParams);
			It.SetScore(TestPurpose, FilterType, bHit, bWantsHit);
		}
	}
}

void UEnvQueryTest_TraceObjectChannel::PostLoad()
{
	Super::PostLoad();
}

FText UEnvQueryTest_TraceObjectChannel::GetDescriptionTitle() const
{
	FString ChannelDesc = *UEnum::GetDisplayValueAsText(TraceType).ToString();

	FString DirectionDesc = TraceFromContext.IsDynamic() ?
		FString::Printf(TEXT("%s, direction: %s"), *UEnvQueryTypes::DescribeContext(Context).ToString(), *TraceFromContext.ToString()) :
		FString::Printf(TEXT("%s %s"), TraceFromContext.DefaultValue ? TEXT("from") : TEXT("to"), *UEnvQueryTypes::DescribeContext(Context).ToString());

	return FText::FromString(FString::Printf(TEXT("%s: %s on %s"), 
		*Super::GetDescriptionTitle().ToString(), *DirectionDesc, *ChannelDesc));
}

FText UEnvQueryTest_TraceObjectChannel::GetDescriptionDetails() const
{
	return FText::Format(FText::FromString("{0}\n{1}"), UEnum::GetDisplayValueAsText(TraceType), DescribeBoolTestParams("hit"));
}

bool UEnvQueryTest_TraceObjectChannel::RunLineTraceTo(const FVector& ItemPos, const FVector& ContextPos, AActor* ItemActor, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	FCollisionQueryParams TraceParams(Params);
	TraceParams.AddIgnoredActor(ItemActor);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(Channel);

	const bool bHit = World->LineTraceTestByObjectType(ContextPos, ItemPos, ObjectParams, TraceParams);
	return bHit;
}

bool UEnvQueryTest_TraceObjectChannel::RunLineTraceFrom(const FVector& ItemPos, const FVector& ContextPos, AActor* ItemActor, UWorld* World, enum ECollisionChannel Channel, const FCollisionQueryParams& Params)
{
	FCollisionQueryParams TraceParams(Params);
	TraceParams.AddIgnoredActor(ItemActor);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(Channel);
	
	const bool bHit = World->LineTraceTestByObjectType(ItemPos,ContextPos, ObjectParams, TraceParams);
	return bHit;
}