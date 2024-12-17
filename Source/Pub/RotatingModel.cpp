// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingModel.h"

// Sets default values
ARotatingModel::ARotatingModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotatingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(RotatingMesh);
	RotatingMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

}

// Called when the game starts or when spawned
void ARotatingModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARotatingModel::ChangeMesh(UStaticMesh* NewMesh)
{
	//RotatingMesh
}

