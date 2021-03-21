// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

UCLASS()
class GETSTARTED_API AInteractableItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableItem();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		class USphereComponent* TriggerVolume;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		UStaticMeshComponent* DisplayMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		UParticleSystemComponent* IdleParticleComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Interactable Item|Particle")
		UParticleSystem* OverlapParticle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Interactable Item|Sounds")
		class USoundCue* OverlapSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Interactable Item|Item Properties")
		bool bNeedRotate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Interactable Item|Item Properties")
		float  RotationRate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
