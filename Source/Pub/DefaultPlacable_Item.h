// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PlacableActor.h"
#include "DefaultPlacable_Item.generated.h"

/**
 * 
 */
UCLASS()
class PUB_API UDefaultPlacable_Item : public UItem
{
	GENERATED_BODY()

protected:

	virtual void Use(class APlayerPawn* Player) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APlacableActor> Placable;
	
};
