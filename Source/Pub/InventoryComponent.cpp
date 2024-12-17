// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Capacity = 20000;


	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}


	// ...
	
}

bool UInventoryComponent::AddItem(UItem* Item)
{
	if (ItemsArray.Num() >= Capacity || !Item)
	{
		/** In case there is no item or capacity is full do not add item */
		return false;
	}

	/** If there is an item and space in capacity add item */
	Item->OwningInventory = this;
	Item->World = GetWorld();
	ItemsArray.Add(Item);
	OnInventoryUpdated.Broadcast();



	return true;
}

bool UInventoryComponent::RemoveItem(UItem* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Item->World = nullptr;
		ItemsArray.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}

	return false;
}

