// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class GETSTARTED_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		class UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnyWhere, Category = "Floating Platform")
		FVector StartPoint;

	UPROPERTY(EditAnyWhere, Category = "Floating Platform", meta = (MakeEditWidget = "true"))
		FVector EndPoint;

	UPROPERTY(EditAnyWhere, Category = "Floating Platform")
		float InterpSpeed;

	UPROPERTY(VisibleAnyWhere, Category = "Floating Platform")
		float Distance;

	UPROPERTY(VisibleAnyWhere, Category = "Floating Platform")
		bool bInterping;

	UPROPERTY(VisibleAnyWhere, Category = "Floating Platform")
		float DelayTime;

	FTimerHandle InterpTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};