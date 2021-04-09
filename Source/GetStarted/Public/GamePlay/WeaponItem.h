// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/InteractableItem.h"
#include "WeaponItem.generated.h"

UENUM(BlueprintType)
enum class EWeaponState :uint8
{
	EWS_CanPickup    UMETA(DisplayName = "CanPickup"),
	EWS_Equipped     UMETA(DisplayName = "Equiped")
};

/**
 *
 */
UCLASS()
class GETSTARTED_API AWeaponItem : public AInteractableItem
{
	GENERATED_BODY()

public:
	AWeaponItem();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Weapon | Sound")
		class USoundCue* OnEquippedSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Weapon | Particle")
		bool bShouldReserveIdleParticle;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Weapon")
		EWeaponState WeaponState;
protected:
	virtual void BeginPlay() override;

public:

	virtual	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip(class AMainPlayer* MainPlayer);

	void UnEquip(AMainPlayer* MainPlayer);

	void ActiveDisplayMeshCollision();

	void DeactiveDisplayMeshCollision();
};
