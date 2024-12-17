// Fill out your copyright notice in the Description page of Project Settings.


#include "PubSimCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APubSimCharacter::APubSimCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	//FQuat QuatRotation = FQuat(FRotator(0, 0, -50));
	//CameraBoom->SetRelativeRotation(QuatRotation);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void APubSimCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APubSimCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCameraFunction();

}

// Called to bind functionality to input
void APubSimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APubSimCharacter::RotateCameraFunction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		RotateInputFloat = EnhancedInputComponent->BindActionValue(RotateCamera).GetValue().Get<float>();
	}

	RotationRate = FMath::Lerp(RotationRate, RotateInputFloat * 2, GetWorld()->GetDeltaSeconds() * 5);
	
	CameraBoom->AddRelativeRotation(FRotator(0, 0, RotationRate));
}

