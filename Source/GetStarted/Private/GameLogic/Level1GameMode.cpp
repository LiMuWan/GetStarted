// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLogic/Level1GameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ALevel1GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainUIClass)
	{
		MainUI = CreateWidget(UGameplayStatics::GetPlayerController(this, 0),MainUIClass);
		if (MainUI)
		{
			MainUI->AddToViewport();
		}
	}
}
