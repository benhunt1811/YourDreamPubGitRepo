// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlacableActor.h"
#include "PlayerNumbersComponent.h"
#include "PlayerPawn.generated.h"



UCLASS()
class PUB_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Input action for rotating the camera */
	UPROPERTY(Category = "Input", EditDefaultsOnly)
	UInputAction* RotateCamera;

	/** Input action for zooming the camera */
	UPROPERTY(Category = "Input", EditDefaultsOnly)
	UInputAction* ZoomCamera;

	/** Input action for moving the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveCamera;

	/** Input action for when placing objects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Place;

	/** Input actions for rotating the placable object */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotatePlacableClockwise;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotatePlacableAntiClockwise;

	/** Input action for resetting the cameras rotation, zoom and position */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ResetCamera;

	struct FEnhancedInputActionValueBinding* MoveActionBinding;

	/** Functions for rotating, zooming, moving and resetting camera */
	UFUNCTION(BlueprintCallable)
	void RotateCameraFunction();
	UFUNCTION(BlueprintCallable)
	void ZoomCameraFunction();
	UFUNCTION(BlueprintCallable)
	void MoveCameraFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void ResetCameraFunction(const FInputActionValue& Value);

	/** Functions for placing objects and rotating them */
	UFUNCTION(BlueprintCallable)
	void PlaceObjectFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void RotatePlacableClockwiseFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void RotatePlacableAntiClockwiseFunction(const FInputActionValue& Value);

	/** Floats for the camera rotation and zoom rates */
	float RotationRate;
	float RotateInputFloat;
	float ZoomInputFloat;

	/** Component for making floating movement for player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UFloatingPawnMovement* MyPawnMoveComp;

	/** Function which is used to try place an object, checking if anything is overlapping */
	UFUNCTION(BlueprintCallable)
	void TryPlace(TSubclassOf<APlacableActor> Placable);

	/** Function for resetting mouse location */
	UFUNCTION(BlueprintCallable)
	void ResetMouseLocation();

	/** Storing the actor that needs to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placable")
	APlacableActor* SpawnActor;

	/** Boolean to tell if the player is currently trying to place an object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placable")
	bool Placing;

	/** Function used for calling items use functions */
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItem* Item);

	/** Creates a player numbers component for player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerNumbersComponent* PlayerNumbersComponent;

	/** Creates an inventory component for storing current spare items */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
	class USoundBase* FinishPlaceSound;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void CreateSaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();


};
