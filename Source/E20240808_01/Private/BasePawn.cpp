// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/BoxComponent.h"
#include "MyPlayerController.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritRoll = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 400.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	OverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCollision"));
	OverlapCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (ABasePawn* otherPawn = Cast<ABasePawn>(OtherActor))
	{
		PossessedPawn = otherPawn;
	}

	Super::NotifyActorBeginOverlap(OtherActor);
}

void ABasePawn::NotifyActorEndOverlap(AActor* OtherActor)
{
	PossessedPawn = nullptr;

	Super::NotifyActorEndOverlap(OtherActor);
}

void ABasePawn::UnPossessed()
{
	AController* controller = GetController();
	AMyPlayerController* cont = Cast< AMyPlayerController>(controller);
	cont->jumpDelegate.Clear();
	cont->stopJumpDelegate.Clear();

	Super::UnPossessed();
}

void ABasePawn::PossessedBy(AController* controller)
{
	AMyPlayerController* cont = Cast< AMyPlayerController>(controller);
	cont->jumpDelegate.AddDynamic(this, &ABasePawn::Jump);
	cont->stopJumpDelegate.AddDynamic(this, &ABasePawn::StopJump);

	Super::PossessedBy(controller);
}

void ABasePawn::Jump()
{
	FVector UpVec = GetActorUpVector();
	float JumpMulti = 30.0f;
	AddActorWorldOffset(UpVec * JumpMulti);
}

void ABasePawn::StopJump()
{
	FVector UpVec = GetActorUpVector();
	float JumpMulti = -30.0f;
	AddActorWorldOffset(UpVec * JumpMulti);
}