// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/WeaponItem.h"
#include "Components/SkeletalMeshComponent.h"

AWeaponItem::AWeaponItem()
{
	DisplayMesh->DestroyComponent();
	DisplayMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DisplaySkeletalMesh"));
	DisplayMesh->SetupAttachment(GetRootComponent());
}