// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class E20240808_01_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* PossessAction;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJumpDelegate);

	UPROPERTY(BlueprintAssignable)
	FJumpDelegate jumpDelegate;
	FJumpDelegate stopJumpDelegate;

	APawn* MyPawn;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump();
	void StopJumping();
	void HasPossess();
	virtual void SetupInputComponent() override;
};
