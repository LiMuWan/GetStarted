// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/TriggerableDoor.h"
#include"Components/BoxComponent.h"
#include "Characters/Player/MainPlayer.h"
// Sets default values
ATriggerableDoor::ATriggerableDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetBoxExtent(FVector(60.0f, 60.0f, 30.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ATriggerableDoor::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerableDoor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerableDoor::OnOverlapEnd);
}

// Called every frame
void ATriggerableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerableDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
	if (MainPlayer)
	{

	}
}

void ATriggerableDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainPlayer* MainPlayer = Cast<AMainPlayer>(OtherActor);
	if (MainPlayer)
	{

	}
}

