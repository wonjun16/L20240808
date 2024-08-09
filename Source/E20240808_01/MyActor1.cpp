// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "Iris/ReplicationSystem/WorldLocations.h"

// Sets default values
AMyActor1::AMyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	this->Location = GetActorLocation();
	this->MaxX = 500;
	this->Speed = 1;
	this->IsUp = true;
}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurLocation = GetActorLocation();

	if (IsUp)
	{
		SetActorLocation(FVector(CurLocation.X + Speed, CurLocation.Y, CurLocation.Z));
		IsUp = (Location.X + MaxX < CurLocation.X) ? false : true;
	}
	else
	{
		SetActorLocation(FVector(CurLocation.X - Speed, CurLocation.Y, CurLocation.Z));
		IsUp = (Location.X - MaxX < CurLocation.X) ? false : true;
	}

}

