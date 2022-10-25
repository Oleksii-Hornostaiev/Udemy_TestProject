// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(Displayname = "Normal"),
	EMS_Sprinting UMETA(Displayname = "Sprinting"),

	EMS_MAX UMETA(Displayname = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(Displayname = "Normal"),
	ESS_BelowMinimum UMETA(Displayname = "BellowMinimum"),
	ESS_Exhausted UMETA(Displayname = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(Displayname = "ExhaustedRecovering"),

	ESS_MAX UMETA(Displayname = "DefaultMAX")
};

UCLASS()
class UDEMY_TESTPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UFUNCTION(BlueprintCallable)
	void ShowPickUpLocations();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AEnemy* CombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector CombatTargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bHasCombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;


	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	FRotator GetLookAtRotationYaw(FVector Target);

	TArray<FVector> PickupLocations;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }
	FORCEINLINE void SetCombatTarget(AEnemy* Enemy) {CombatTarget = Enemy; }
	FORCEINLINE void SetHasCombatTarger(bool HasTarget) { bHasCombatTarget = HasTarget; }

	/** Set movement status and movement speed */
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	/** Pressed shift key down to enable sprinting */
	void ShiftKeyDown();

	/** Released shift key to stop sprinting */
	void ShiftKeyUp();


	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAcess = true))
	class UCameraComponent* FollowCamera;

	/** CameraBoom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAcess = true))
	class USpringArmComponent* CameraBoom;

	/* Base turn rates to scale turning functions for the camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	/**
	 *
	 * Player Stats
	 *
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;

	virtual float TakeDamage( float DamageAmount,
    struct FDamageEvent const & DamageEvent,
    class AController * EventInstigator,
    AActor * DamageCauser ) override;

	void DecrementHealth(float Amount);

	void Die();

	void IncrementCoin(int32 Amount);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called for forwards / backwards input
	void MoveForward(float Value);

	// Called for side ti side input
	void MoveRight(float Value);

	/*  Called via input to turn at a given rate
	 *  @param Rate this is normalize rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/*  Called via input to look up/down at a given rate
	 *  @param Rate this is normalize rate, i.e. 1.0 means 100% of desired look up/down rate
	 */
	void LookUpAtRate(float Rate);

	bool bLMBDOwn;
	void LMBDown();
	void LMBUp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AItem_Weapon* EquipedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlapingItem;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	void SetEquippedWeapon(AItem_Weapon* WeaponToSet);
	FORCEINLINE void SetActiveOverlapingItem(AItem* ItemToSet) { ActiveOverlapingItem = ItemToSet; }
	FORCEINLINE class AItem_Weapon* GetEquipedWeapon() { return EquipedWeapon; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();
};
