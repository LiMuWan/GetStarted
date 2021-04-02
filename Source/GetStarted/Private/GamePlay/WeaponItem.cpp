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