// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/FloatingPlatform.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	RootComponent = PlatformMesh;

	StartPoint = FVector(0.0f);
	EndPoint = FVector(0.0f);

	InterpSpeed = 200.0f;
	Distance = 0.0f;
	bInterping = true;
	DelayTime = 1.0f;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint = StartPoint + EndPoint;
	Distance = (EndPoint - StartPoint).Size();
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterping)
	{
		const FVector Current = GetActorLocation();
		const FVector InterpLocation = FMath::VInterpConstantTo(Current, EndPoint, DeltaTime, InterpSpeed);
		SetActorLocation(InterpLocation);

		const float NowDistance = (GetActorLocation() - StartPoint).Size();
		/*UE_LOG(LogTemp, Warning, TEXT("%f"), NowDistance);*/
		if (Distance - NowDistance <= 0.5f)
		{
			const auto ToggleInterpingState = [this]()
			{
				bInterping = !bInterping;
			};

			ToggleInterpingState();

			GetWorldTimerManager().SetTimer(InterpTimerHandle, FTimerDelegate::CreateLambda(ToggleInterpingState), DelayTime, false);

			const FVector TempVec = StartPoint;
			StartPoint = EndPoint;
			EndPoint = TempVec;
		}
	}
}

