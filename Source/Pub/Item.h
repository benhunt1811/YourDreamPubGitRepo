// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RotatingModel.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class PUB_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	class UWorld* World;

	/** Setting a thumbnail for the image that appears on store/inventory widget */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	/** Main name for item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	/** How much it is to buy */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	float Cost;

	/** Player level required to buy item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int LevelNeeded;

	/** Description of item */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	/** Getting owned inventory */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UInventoryComponent* OwningInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<ARotatingModel> RotatingModelActor;

	/** Functions for when the item is being used/placed */
	virtual void Use(class APlayerPawn* Player) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class APlayerPawn* PlayerPawn);
	
};
