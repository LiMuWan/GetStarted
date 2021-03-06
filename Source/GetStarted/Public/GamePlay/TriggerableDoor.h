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

	UPROPERTY(BlueprintReadWrite, Category = "Trigger Door | Trigger Properties")
		FVector InitTriggerLocation;

	UPROPERTY(BlueprintReadWrite, Category = "Trigger Door | Door Properties")
		FVector InitDoorLocation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Trigger Door | Door Properties")
		float DelayTime;

	FTimerHandle CloseDoorTimerHandle;

	bool bIsPlayerOnTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door | Trigger Switch ")
		void RaiseTrigger();

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door | Trigger Switch ")
		void LowerTrigger();

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door | Door Switch ")
		void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggerable Door | Door Switch ")
		void CloseDoor();

	UFUNCTION(BlueprintCallable, Category = "Trigger Door | Trigger Switch")
		void UpdateTriggerLocation(FVector Offset);

	UFUNCTION(BlueprintCallable, Category = "Trigger Door | Door Switch")
		void UpdateDoorLocation(FVector Offset);
};
