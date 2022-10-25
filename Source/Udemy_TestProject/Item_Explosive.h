// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Explosive.generated.h"

/**
 * 
 */
UCLASS()
class UDEMY_TESTPROJECT_API AItem_Explosive : public AItem
{
	GENERATED_BODY()

public:
	AItem_Explosive();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage;

	// UFUNCTION() INHERITANCE FROM PARENT CLASS
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult & SweepResult
	) override;

	// UFUNCTION() INHERITANCE FROM PARENT CLASS
	virtual void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	) override;
};
