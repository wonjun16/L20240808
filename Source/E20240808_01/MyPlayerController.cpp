// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

void AMyPlayerController::Move(const FInputActionValue& value)
{

	// input is a Vector2D
	FVector2D MovementVector = value.Get<FVector2D>();


	// find out which way is forward
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	MyPawn = GetPawn();
	// add movement 
	if (MyPawn)
	{
		MyPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		MyPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyPlayerController::Look(const FInputActionValue& value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = value.Get<FVector2D>();

	// add yaw and pitch input to controller
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AMyPlayerController::Jump()
{
	MyPawn = GetPawn();
	if (ACharacter* character = Cast<ACharacter>(MyPawn))
	{
		character->Jump();
	}
	else
	{
		FVector UpVec = MyPawn->GetActorUpVector();
		float JumpMulti = 30.0f;

		MyPawn->AddActorWorldOffset(UpVec * JumpMulti);
	}
}

void AMyPlayerController::StopJumping()
{
	MyPawn = GetPawn();
	if (ACharacter* character = Cast<ACharacter>(MyPawn))
	{
		character->StopJumping();
	}
	else
	{
		FVector UpVec = MyPawn->GetActorUpVector();
		float JumpMulti = -30.0f;

		MyPawn->AddActorWorldOffset(UpVec * JumpMulti);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::Look);
	}
}