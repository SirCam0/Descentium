// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4265)
#include "Steam/steam_api.h"
#pragma warning(pop)

#include "DescentiumGameModeBase.generated.h"

#define RAW_APP_ID "1927600"

/**
 * 
 */
UCLASS()
class DESCENTIUM_API ADescentiumGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	static constexpr char* APP_ID = RAW_APP_ID;
	CSteamID MyID;
};
