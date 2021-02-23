// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerableDoor.generated.h"

UCLASS()
class GETSTARTED_API ATriggerableDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerableDoor();

public:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		class UStaticMeshComponent* TriggerMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		class UStaticMeshComponent* DoorMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
