// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacableActor.generated.h"

UCLASS()
class PUB_API APlacableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlacableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Mesh for PlacableActor */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	/** Hitbox for the main mesh */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* HitboxMesh;

	/** Used to check if there is any obstructions when placing item */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "BoolChecks")
	bool CanSpawn;

	/** Array used to store materials which are then put on mesh once placed */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Materials")
	TArray <UMaterialInterface*> Material;

	/** Green material used when object placable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* GreenMat;

	/** Red material used for when object is not placable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* RedMat;

	/** Function used to check if object can spawn */
	UFUNCTION(BlueprintCallable)
	void CheckSpawn();

	/** Function for placing object, updating material and mesh */
	UFUNCTION(BlueprintCallable)
	void Place();

	/** String for what type of object the actor is, e.g. entertainment or style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjType")
	FString ObjectType;

	/** Int used to show how much the object will increase the players levels */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjType")
	int ObjectValue;

	/** Boolean for if the actor has been placed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoolChecks")
	bool HasBeenPlaced;

	/** Function for updating the players levels when object is placed */
	void AddPlacedItem();

	/** Function for updating the players levels when object is removed */
	UFUNCTION(BlueprintCallable)
	void RemovePlacedItem();



};
