// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/WeaponItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AWeaponItem::AWeaponItem()
{
	TriggerVolume->SetSphereRadius(64.0f);
	DisplayMesh->DestroyComponent();
	DisplayMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DisplaySkeletalMesh"));
	DisplayMesh->SetupAttachment(GetRootComponent());
}

void AWeaponItem::BeginPlay()
{
}

void AWeaponItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeaponItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeaponItem::Equip()
{
}

void AWeaponItem::UnEquip()
{
}
