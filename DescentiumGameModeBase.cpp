// Copyright Epic Games, Inc. All Rights Reserved.


#include "DescentiumGameModeBase.h"

void ADescentiumGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FFileHelper::SaveStringToFile(TEXT(RAW_APP_ID),	TEXT("steam_appid.txt"));

	SteamAPI_RestartAppIfNecessary(atoi(APP_ID));

	if (SteamAPI_Init())
	{
		MyID = SteamUser()->GetSteamID();
		//GEngine->AddOnScreenDebugMessage(-1,50,FColor::Green, FString::Printf(TEXT("Beginning play")));
	}
}
