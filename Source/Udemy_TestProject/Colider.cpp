// Fill out your copyright notice in the Description page of Project Settings.


#include "Colider.h"

#include "ColiderMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AColider::AColider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/TutorialAssets/MeshTools/SM_Sphere.SM_Sphere'"));
	if(MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
		MeshComponent->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UColiderMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraInput = FVector2D(0.0f);
}

// Called when the game starts or when spawned
void AColider::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AColider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation Yaw (Mesh)
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	//Rotation Pitch (SpringArmComp)
	FRotator NewSpringArmRotation = SpringArmComponent->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.0f, -15.0f);

	SpringArmComponent->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void AColider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AColider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AColider::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &AColider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &AColider::YawCamera);
}

void AColider::MoveForward(float Input)
{
	FVector Forward = GetActorForwardVector();
	
		if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Forward * Input);
	}
}

void AColider::MoveRight(float Input)
{
	FVector Right = GetActorRightVector();

	if (OurMovementComponent)
	{
		OurMovementComponent->AddInputVector(Right * Input);
	}
}

UColiderMovementComponent* AColider::GetOurMovementComponent() const
{
	return OurMovementComponent;
}

void AColider::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
	
}

void AColider::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}



