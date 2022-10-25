// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_PickUp.h"

#include "MainCharacter.h"

AItem_PickUp::AItem_PickUp()
{
	CoinCount = 1;
}

void AItem_PickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if(Main)
		{
			Main->IncrementCoin(CoinCount);
			Main->PickupLocations.Add(GetActorLocation());

			Destroy();
		}
	}
}

void AItem_PickUp::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}
