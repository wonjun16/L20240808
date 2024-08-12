// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class E20240808_01_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArmComponent;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	class UFloatingPawnMovement* FloatingPawnMovement;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	class UBoxComponent* OverlapCollision;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	class ABasePawn* PossessedPawn;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void UnPossessed() override;
	virtual void PossessedBy(AController*) override;
	UFUNCTION()
	void Jump();
	UFUNCTION()
	void StopJump();
};
