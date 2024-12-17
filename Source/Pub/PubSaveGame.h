// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlacableActor.h"
#include "PubSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PUB_API UPubSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPubSaveGame();

	UPROPERTY(EditAnywhere)
	float SaveMoneyValue;

	UPROPERTY(EditAnywhere)
	int SaveCapacityValue;

	UPROPERTY(EditAnywhere)
	int SaveEntertainmentValue;

	UPROPERTY(EditAnywhere)
	int SaveStyleValue;

	UPROPERTY(EditAnywhere)
	int SaveCurrentLevel;

	UPROPERTY(EditAnywhere)
	int SaveCurrentXP;

	UPROPERTY(EditAnywhere)
	int SaveMaxXP;

	UPROPERTY(EditAnywhere)
	float SaveNPCMoneyAmount;

	UPROPERTY(EditAnywhere)
	TMap<class TSubclassOf<APlacableActor>, FVector > SavedPlacableItems;
	
};
