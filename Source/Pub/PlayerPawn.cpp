// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "PubSaveGame.h"
#include "Item.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	//FQuat QuatRotation = FQuat(FRotator(0, 0, -50));
	//CameraBoom->SetRelativeRotation(QuatRotation);

	CameraBoom->SetRelativeRotation(FRotator(0, -50, -50));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	MyPawnMoveComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMoveComp"));

	PlayerNumbersComponent = CreateDefaultSubobject<UPlayerNumbersComponent>(TEXT("NumbersComponent"));

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	Inventory->Capacity = 20;

	FinishPlaceSound = CreateDefaultSubobject<USoundBase>(TEXT("FinishPlaceSound"));

	Placing = false;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	LoadGame();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCameraFunction();
	ZoomCameraFunction();

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerPawn::MoveCameraFunction);

		EnhancedInputComponent->BindAction(Place, ETriggerEvent::Triggered, this, &APlayerPawn::PlaceObjectFunction);

		EnhancedInputComponent->BindAction(RotatePlacableClockwise, ETriggerEvent::Started, this, &APlayerPawn::RotatePlacableClockwiseFunction);
		EnhancedInputComponent->BindAction(RotatePlacableAntiClockwise, ETriggerEvent::Started, this, &APlayerPawn::RotatePlacableAntiClockwiseFunction);

		EnhancedInputComponent->BindAction(ResetCamera, ETriggerEvent::Started, this, &APlayerPawn::ResetCameraFunction);
	}

}

void APlayerPawn::RotateCameraFunction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		RotateInputFloat = EnhancedInputComponent->BindActionValue(RotateCamera).GetValue().Get<float>();
	}

	RotationRate = FMath::Lerp(RotationRate, RotateInputFloat * 2, GetWorld()->GetDeltaSeconds() * 5);

	CameraBoom->AddRelativeRotation(FRotator(0, RotationRate, 0));

}

void APlayerPawn::ZoomCameraFunction()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		ZoomInputFloat = EnhancedInputComponent->BindActionValue(ZoomCamera).GetValue().Get<float>();
	}

	ZoomInputFloat *= -1;

	float ZoomRate = FMath::Lerp(ZoomRate, ZoomInputFloat * 1000, GetWorld()->GetDeltaSeconds() * 5);

	ZoomRate = ZoomRate + CameraBoom->TargetArmLength;

	ZoomRate = FMath::Clamp(ZoomRate, 500, 2000);

	CameraBoom->TargetArmLength = ZoomRate;
}

void APlayerPawn::MoveCameraFunction(const FInputActionValue& Value)
{

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	float NormalizeTolerance = 0.0001;

	float MovementSlower = 1;

	if (Placing)
	{
		MovementSlower = 2;
	}

	else
	{
		MovementSlower = 1.2;
	}

	FVector CamRightVector = CameraBoom->GetRightVector();
	CamRightVector.Z = 0;
	CamRightVector.Normalize(NormalizeTolerance);
	AddMovementInput(CamRightVector, MovementVector.X / MovementSlower);
	
	FVector CamForwardVector = CameraBoom->GetForwardVector();
	CamForwardVector.Z = 0;
	CamForwardVector.Normalize(NormalizeTolerance);
	AddMovementInput(CamForwardVector, MovementVector.Y / MovementSlower);

}

void APlayerPawn::PlaceObjectFunction(const FInputActionValue& Value)
{
	if (SpawnActor)
	{
		SpawnActor->Place();

		if (SpawnActor->CanSpawn)
		{
			Placing = false;
			SpawnActor = NULL;

			if (FinishPlaceSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), FinishPlaceSound, 1, 1, 0, NULL, NULL, true);
			}
		}
	}
}

void APlayerPawn::RotatePlacableClockwiseFunction(const FInputActionValue& Value)
{
	if (Placing)
	{
		if (SpawnActor)
		{
			SpawnActor->AddActorWorldRotation(FRotator(0, -10, 0));
		}
	}
}

void APlayerPawn::RotatePlacableAntiClockwiseFunction(const FInputActionValue& Value)
{
	if (Placing)
	{
		if (SpawnActor)
		{
			SpawnActor->AddActorWorldRotation(FRotator(0, 10, 0));
		}
	}
}

void APlayerPawn::ResetCameraFunction(const FInputActionValue& Value)
{
	CameraBoom->SetRelativeRotation(FRotator(-50, 0, 0));
	CameraBoom->TargetArmLength = 1200;
}

void APlayerPawn::TryPlace(TSubclassOf<APlacableActor> Placable)
{

	if (Placing)
	{
		FHitResult OutHit;
		FVector Start = CameraBoom->GetComponentLocation();
		FVector ForwardVector = CameraBoom->GetForwardVector();

		FVector End = ((ForwardVector * 3000) + Start);

		/** Makes the raycast ignore the player */
		FCollisionQueryParams CollisionParams;
		//CollisionParams.AddIgnoredActor(this->GetOwner());
		
		/** Uses a line trace to get where the object should be placed, also double checking 
			that theres no objects in the way */
		bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

		if (IsHit)
		{
			if (IsValid(SpawnActor))
			{
				SpawnActor->SetActorLocation(OutHit.Location);
				SpawnActor->CheckSpawn();
			}

			if (!IsValid(SpawnActor))
			{
				FActorSpawnParameters SpawnInfo;
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FVector Location = OutHit.Location;

				SpawnActor = GetWorld()->SpawnActor<APlacableActor>(Placable, Location, Rotation);

				for (int i = 0; i < SpawnActor->Mesh->GetNumMaterials(); i++)
				{
					SpawnActor->Material.Add(SpawnActor->Mesh->GetMaterial(i));
				}
				SpawnActor->CheckSpawn();


			}
		}

		if (!IsHit)
		{
			if (IsValid(SpawnActor))
			{
				SpawnActor->Destroy();
			}
		}
	}
}

void APlayerPawn::ResetMouseLocation()
{
	APlayerController* PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);

	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}

	float ScreenX = Result.X / 2;
	ScreenX = FMath::TruncToFloat(ScreenX);

	float ScreenY = Result.Y / 2;
	ScreenY = FMath::TruncToFloat(ScreenY);

	if (PlayerController)
	{
		PlayerController->SetMouseLocation(ScreenX, ScreenY);
	}
}

void APlayerPawn::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); // BP Event
	}
}

void APlayerPawn::SaveGame()
{

	// Loads game into the instance
	UPubSaveGame* SaveGameInstance = Cast<UPubSaveGame>(UGameplayStatics::LoadGameFromSlot("PubSaveSlot", 0));

	if (SaveGameInstance != nullptr)
	{
		// Saving money values
		SaveGameInstance->SaveMoneyValue = PlayerNumbersComponent->OnScreenMoneyValue;
		SaveGameInstance->SaveCapacityValue = PlayerNumbersComponent->CapacityLevel;
		SaveGameInstance->SaveEntertainmentValue = PlayerNumbersComponent->EntertainmentLevel;
		SaveGameInstance->SaveStyleValue = PlayerNumbersComponent->StyleLevel;
		SaveGameInstance->SaveCurrentLevel = PlayerNumbersComponent->CurrentLevel;
		SaveGameInstance->SaveCurrentXP = PlayerNumbersComponent->CurrentXP;
		SaveGameInstance->SaveMaxXP = PlayerNumbersComponent->MaxXP;
		SaveGameInstance->SaveNPCMoneyAmount = PlayerNumbersComponent->NPCMoneyAmount;

		// Saves game instance
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PubSaveSlot"), 0);
	}

	else if (!UGameplayStatics::DoesSaveGameExist("PubSaveSlot", 0))
	{
		CreateSaveGame();
	}
}

void APlayerPawn::CreateSaveGame()
{
	// Creates save instance
	UPubSaveGame* SaveGameInstance = Cast<UPubSaveGame>(UGameplayStatics::CreateSaveGameObject(UPubSaveGame::StaticClass()));

	// Saves game instance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PubSaveSlot"), 0);
}

void APlayerPawn::LoadGame()
{
	// Loads game into the instance
	UPubSaveGame* SaveGameInstance = Cast<UPubSaveGame>(UGameplayStatics::LoadGameFromSlot("PubSaveSlot", 0));

	if (SaveGameInstance != nullptr)
	{
		PlayerNumbersComponent->OnScreenMoneyValue = SaveGameInstance->SaveMoneyValue;
		PlayerNumbersComponent->CapacityLevel = SaveGameInstance->SaveCapacityValue;
		PlayerNumbersComponent->EntertainmentLevel = SaveGameInstance->SaveEntertainmentValue;
		PlayerNumbersComponent->StyleLevel = SaveGameInstance->SaveStyleValue;
		PlayerNumbersComponent->CurrentLevel = SaveGameInstance->SaveCurrentLevel;
		PlayerNumbersComponent->CurrentXP = SaveGameInstance->SaveCurrentXP;
		PlayerNumbersComponent->MaxXP = SaveGameInstance->SaveMaxXP;
		PlayerNumbersComponent->NPCMoneyAmount = SaveGameInstance->SaveNPCMoneyAmount;

	}

	else if (!UGameplayStatics::DoesSaveGameExist("PubSaveSlot", 0))
	{
		CreateSaveGame();
	}

}


