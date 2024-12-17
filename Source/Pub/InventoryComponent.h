// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUB_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	/** Adding an item to the inventory */
	UFUNCTION(BlueprintCallable)
	bool AddItem(class UItem* Item);
	
	/** Removing item from inventory */
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(class UItem* Item);

	/** Default items the player gets at the start of the game */
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Inventory")
	TArray<class UItem*> DefaultItems;

	/** Inventory capacity for items */
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	/** Used to broadcast when the inventory is updated */
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	/** Array used to store current items the player has */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class UItem*> ItemsArray;

};
