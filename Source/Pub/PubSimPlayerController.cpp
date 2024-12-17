// Fill out your copyright notice in the Description page of Project Settings.


#include "PubSimPlayerController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerPawn.h"
#include "Misc/App.h"

void APubSimPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			MoveActionBinding = &EnhancedInputComponent->BindActionValue(RotateCamera);
		}
	}
}


void APubSimPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* ControlledPawn = GetPawn();

	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(ControlledPawn);

	if (PlayerPawn)
	{
		PlayerPawn->CameraBoom->AddRelativeRotation(FRotator(0, 5, 5));

	}
}

void APubSimPlayerController::RotateCameraFunction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		RotateInputFloat = EnhancedInputComponent->BindActionValue(RotateCamera).GetValue().Get<float>();
	}

	RotationRate = FMath::Lerp(RotationRate, RotateInputFloat * 2, GetWorld()->GetDeltaSeconds() * 5);

	APawn* ControlledPawn = GetPawn();

	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(ControlledPawn);

	if (PlayerPawn)
	{
		PlayerPawn->CameraBoom->AddRelativeRotation(FRotator(0, 0, RotationRate));
		
	}

}
