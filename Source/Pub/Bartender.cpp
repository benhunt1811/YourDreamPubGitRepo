// Fill out your copyright notice in the Description page of Project Settings.


#include "Bartender.h"

// Sets default values
ABartender::ABartender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABartender::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABartender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

