// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawn.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	CountMax = 5;

	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Count += DeltaTime;

	if (Count >= CountMax)
	{
		PayMoney();
	}

}

void ANPC::PayMoney()
{
	Count = 0;
	if (Player)
	{
		Player->PlayerNumbersComponent->MoneyValue += Player->PlayerNumbersComponent->NPCMoneyAmount;
		Player->PlayerNumbersComponent->OnScreenMoneyValue = Player->PlayerNumbersComponent->MoneyValue;

		OnMoneyAdded.Broadcast();
	}
}

