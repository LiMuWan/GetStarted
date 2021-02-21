// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MainPlayerAnimInstance.h"
#include "Characters/Player/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainPlayerAnimInstance::NativeInitializeAnimation()
{
	PlayerRef = Cast<AMainPlayer>(TryGetPawnOwner());
}

void UMainPlayerAnimInstance::UpdateAnimationProperties()
{
	if (PlayerRef == nullptr)
	{
		PlayerRef = Cast<AMainPlayer>(TryGetPawnOwner());
	}

	if (PlayerRef != nullptr)
	{
		const FVector SpeedVector = PlayerRef->GetVelocity();
		const FVector PlanarSpeed = FVector(SpeedVector.X, SpeedVector.Y, 0.0f);
		Speed = PlanarSpeed.Size();

		bIsInAir = PlayerRef->GetMovementComponent()->IsFalling();
	}
}
