// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Explosive.h"

#include "MainCharacter.h"

AItem_Explosive::AItem_Explosive()
{
	Damage = 15.0f;
}

void AItem_Explosive::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT(" AItem_Explosive::OnOverlapBegin "));
	if(OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if(Main)
		{
			Main->DecrementHealth(Damage);

			Destroy();
		}
	}
}

void AItem_Explosive::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Warning, TEXT(" AItem_Explosive::OnOverlapEnd "));
}
