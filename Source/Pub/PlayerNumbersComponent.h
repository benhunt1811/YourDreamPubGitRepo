// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerNumbersComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUB_API UPlayerNumbersComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerNumbersComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Current player level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XPSystem")
	int CurrentLevel;

	/** Current player xp  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XPSystem")
	int CurrentXP;

	/** XP player needs to level up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XPSystem")
	int MaxXP;

	/** Amount of money NPCs will give each few seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XPSystem")
	float NPCMoneyAmount;

	/** How much money the player has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float MoneyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float OnScreenMoneyValue;

	/** Various levels for the players pub stats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int CapacityLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int EntertainmentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int StyleLevel;

	/** Used to broadcast when the inventory is updated */
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnLevelUp OnLevelUp;

	/** Function when the player reaches MaxXP, boosting the players level by one */
	UFUNCTION(BlueprintCallable)
	void IncreaseLevel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
	class USoundBase* LevelUpSound;

	void UpdateNPCMoneyAmount();

};
