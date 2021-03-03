// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASpawVolume.generated.h"

UCLASS()
class GETSTARTED_API AASpawVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AASpawVolume();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		class UBoxComponent* SpawnBox;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Spawn Volume")
		TArray<TSubclassOf<AActor>>	SpawActorClassesArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn Volume")
		FVector GetSpawnPoint();

	UFUNCTION(BlueprintCallable, Category = "Spawn Volume")
		TSubclassOf<AActor> GetSpawnActorClass();
};
