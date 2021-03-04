// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/ASpawVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AASpawVolume::AASpawVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));

	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void AASpawVolume::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AASpawVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AASpawVolume::GetSpawnPoint()
{
	const FVector Orgin = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();
	return UKismetMathLibrary::RandomPointInBoundingBox(Orgin, Extent);
}

TSubclassOf<AActor> AASpawVolume::GetSpawnActorClass()
{
	if (SpawActorClassesArray.Num() > 0)
	{
		int index = FMath::FRandRange(0, SpawActorClassesArray.Num() - 1);
		return SpawActorClassesArray[index];
	}
	else
	{
		return nullptr;
	}
}

void AASpawVolume::SpawnActor_Implementation(UClass* SpawnClass, FVector SpawnLocation)
{
	if (SpawnClass)
	{
		GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnLocation, FRotator(0.0f));
	}
}

