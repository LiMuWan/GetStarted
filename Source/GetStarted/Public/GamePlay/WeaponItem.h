// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/InteractableItem.h"
#include "WeaponItem.generated.h"

/**
 *
 */
UCLASS()
class GETSTARTED_API AWeaponItem : public AInteractableItem
{
	GENERATED_BODY()

public:
	AWeaponItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Weapon|Sound")
		class USoundCue* OnEquippedSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Weapon|Particle")
		bool bShouldReserveIdleParticle;
public:

	virtual	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip();

	void UnEquip();
};
