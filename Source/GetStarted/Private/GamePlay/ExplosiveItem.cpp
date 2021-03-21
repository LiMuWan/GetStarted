// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/ExplosiveItem.h"
#include "Characters/Player/MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"

AExplosiveItem::AExplosiveItem()
{
	TriggerVolume->SetSphereRadius(50.0f);
	Damage = 20.0f;
}

void AExplosiveItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, DamageTypeClass);
		Destroy();
	}
}

void AExplosiveItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

