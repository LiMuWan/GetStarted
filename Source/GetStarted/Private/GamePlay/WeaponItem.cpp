// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/WeaponItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/Player/MainPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

AWeaponItem::AWeaponItem()
{
	TriggerVolume->SetSphereRadius(64.0f);
	DisplayMesh->DestroyComponent();
	DisplayMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DisplaySkeletalMesh"));
	DisplayMesh->SetupAttachment(GetRootComponent());
	ActiveDisplayMeshCollision();

	static ConstructorHelpers::FObjectFinder<USoundCue> SoundCueAsset(TEXT("SoundCue'/Game/Assets/Audios/Blade_Cue.Blade_Cue'"));
	if (SoundCueAsset.Succeeded())
	{
		OnEquippedSound = SoundCueAsset.Object;
	}

	bShouldReserveIdleParticle = false;
	WeaponState = EWeaponState::EWS_CanPickup;
}

void AWeaponItem::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor && WeaponState == EWeaponState::EWS_CanPickup)
	{
		AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
		if (MainPlayer)
		{
			MainPlayer->OverLappingWeapon = this;
		}
	}
}

void AWeaponItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
		if (MainPlayer && MainPlayer->OverLappingWeapon == this)
		{
			MainPlayer->OverLappingWeapon = nullptr;
		}
	}
}

void AWeaponItem::Equip(AMainPlayer* MainPlayer)
{
	if (MainPlayer)
	{
		WeaponState = EWeaponState::EWS_Equipped;
		DeactiveDisplayMeshCollision();

		const USkeletalMeshSocket* RightHandSocket = MainPlayer->GetMesh()->GetSocketByName("RightHandSocket");
		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, MainPlayer->GetMesh());
			MainPlayer->bHasWeapon = true;
			MainPlayer->EquippedWeapon = this;
			MainPlayer->OverLappingWeapon = nullptr;

			bNeedRotate = false;
			if (OnEquippedSound)
			{
				UGameplayStatics::PlaySound2D(this, OnEquippedSound);
			}

			if (!bShouldReserveIdleParticle)
			{
				IdleParticleComponent->Deactivate();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("RightHandSocket is null"));
		}
	}
}

void AWeaponItem::UnEquip(AMainPlayer* MainPlayer)
{
	// 如果不是跳跃状态
	if (MainPlayer && !MainPlayer->GetMovementComponent()->IsFalling())
	{
		WeaponState = EWeaponState::EWS_CanPickup;
		ActiveDisplayMeshCollision();

		MainPlayer->bHasWeapon = false;
		MainPlayer->EquippedWeapon = nullptr;
		if (MainPlayer->OverLappingWeapon == nullptr)
		{
			MainPlayer->OverLappingWeapon = this;
		}

		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SetActorRotation(FRotator(0.0f));
		SetActorScale3D(FVector(1.0f));
	}
}

void AWeaponItem::ActiveDisplayMeshCollision()
{
	DisplayMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	DisplayMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	DisplayMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DisplayMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void AWeaponItem::DeactiveDisplayMeshCollision()
{
	DisplayMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
