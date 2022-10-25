// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Colider.generated.h"

UCLASS()
class UDEMY_TESTPROJECT_API AColider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AColider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UColiderMovementComponent* OurMovementComponent;

	virtual UColiderMovementComponent* GetOurMovementComponent() const;
	

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh) { MeshComponent = Mesh;}
	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereConponent(USphereComponent* Sphere) { SphereComponent = Sphere;}
	FORCEINLINE UCameraComponent* GetCameraComponent() { return CameraComponent; }
	FORCEINLINE void SetCameraComponent(UCameraComponent* Camera) { CameraComponent = Camera;}
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArmComponent; }
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* SprigArm) { SpringArmComponent = SprigArm;}

private:

	void MoveForward(float Input);
	void MoveRight(float Input);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

	FVector2D CameraInput;
};
