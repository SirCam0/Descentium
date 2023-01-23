// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavMeshNodeInterface.generated.h"

class ANavMeshNode;
/**
 * 
 */
UINTERFACE(MinimalAPI)
class UNavMeshNodeInterface : public UInterface
{
 GENERATED_BODY()
};


class DESCENTIUM_API INavMeshNodeInterface
{
 GENERATED_BODY()

public:
 UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=A3DNavMesh)
 ANavMeshNode* GetNavMeshNodeREF();
};