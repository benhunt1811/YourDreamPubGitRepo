// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPawn.h"
#include "NPC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoneyAdded);

UCLASS()
class PUB_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Player reference */
	APlayerPawn* Player;

	/** Floats used for timers */
	float Count;
	float CountMax;

	/** Used to broadcast when the inventory is updated */
	UPROPERTY(BlueprintAssignable, Category = "NPC")
	FOnMoneyAdded OnMoneyAdded;

	/** Function for adding money to the player */
	void PayMoney();





};
