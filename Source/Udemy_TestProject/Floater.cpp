// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	InnitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);
	InnitialDirection = FVector(0.0f, 0.0f, 0.0f);
	InnitialForce = FVector (2000000.0f, 0.0f, 0.0f);
	InnitialTorque = FVector (2000000.0f, 0.0f, 0.0f);

	bInnitializeFloaterLocation = false;
	bShouldFloat = false;

	RunningTime = 0.0f;

	A = 0.0f;
	B = 0.0f;
	C = 0.0f;
	D = 0.0f;

}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	float InnitialX = FMath::FRandRange(-500.0f, 500.0f);
	float InnitialY = FMath::FRandRange(-500.0f, 500.0f);
	float InnitialZ = FMath::FRandRange(0.0f, 500.0f);

	InnitialLocation.X = InnitialX;
	InnitialLocation.Y = InnitialY;
	InnitialLocation.Z = InnitialZ;

	PlacedLocation = GetActorLocation();

	if(bInnitializeFloaterLocation)
	{
		SetActorLocation(InnitialLocation);
	}

	BaseZLocation = PlacedLocation.Z;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldFloat)
	{
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + A *  FMath::Sin(B * RunningTime - C) +D; /// Period = PI / ABS(B)

		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
	}
}

