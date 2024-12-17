// Fill out your copyright notice in the Description page of Project Settings.

#include "PlacableActor.h"
#include "PlayerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlacableActor::APlacableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Mesh->SetRelativeLocation(FVector(0, -50, -20));

	HitboxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HitboxMesh"));
	HitboxMesh->SetupAttachment(Mesh);
	HitboxMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));


}

// Called when the game starts or when spawned
void APlacableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlacableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlacableActor::CheckSpawn()
{
	/** Checking for overlapping actors */
	TArray<AActor*> Result;
	//GetOverlappingActors(Result);

	Mesh->GetOverlappingActors(Result);

	if (Result.Num() > 0)
	{
		CanSpawn = false;
		for (int i = 0; i < Material.Num(); i++)
		{
			Mesh->SetMaterial(i, RedMat);
		}

		HasBeenPlaced = false;
	}

	else
	{
		CanSpawn = true;
		for (int i = 0; i < Material.Num(); i++)
		{
			Mesh->SetMaterial(i, GreenMat);
		}

		HasBeenPlaced = false;
	}
}

void APlacableActor::Place()
{
	if (CanSpawn)
	{
		/** Updates to correct materials */
		for (int i = 0; i < Material.Num(); i++)
		{
			Mesh->SetMaterial(i, Material[i]);
		}

		/** Updates collisions once placed */
		Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));
		HasBeenPlaced = true;
		
		AddPlacedItem();
	}
}

void APlacableActor::AddPlacedItem()
{
	APlayerPawn* Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		if (ObjectType == "Capacity")
		{
			Player->PlayerNumbersComponent->CapacityLevel += ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP += ObjectValue;
		}

		if (ObjectType == "Entertainment")
		{
			Player->PlayerNumbersComponent->EntertainmentLevel += ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP += ObjectValue;
		}

		if (ObjectType == "Style")
		{
			Player->PlayerNumbersComponent->StyleLevel += ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP += ObjectValue;
		}

		Player->PlayerNumbersComponent->UpdateNPCMoneyAmount();
	}
}

void APlacableActor::RemovePlacedItem()
{
	APlayerPawn* Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		if (ObjectType == "Capacity")
		{
			Player->PlayerNumbersComponent->CapacityLevel -= ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP -= ObjectValue;
		}

		if (ObjectType == "Entertainment")
		{
			Player->PlayerNumbersComponent->EntertainmentLevel -= ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP -= ObjectValue;
		}

		if (ObjectType == "Style")
		{
			Player->PlayerNumbersComponent->StyleLevel -= ObjectValue;
			Player->PlayerNumbersComponent->CurrentXP -= ObjectValue;
		}

		Player->PlayerNumbersComponent->UpdateNPCMoneyAmount();

	}
}

