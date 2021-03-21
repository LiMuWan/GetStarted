// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/PickupItem.h"
#include "Characters/Player/MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

APickupItem::APickupItem()
{

}

void APickupItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		const AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
		if (OverlapParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, OverlapParticle, GetActorLocation(), FRotator(0.0f), true);
		}
		if (OverlapSound)
		{
			UGameplayStatics::SpawnSound2D(this, OverlapSound);
		}

		OnPickup(MainPlayer);
		Destroy();
	}
}

void APickupItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
