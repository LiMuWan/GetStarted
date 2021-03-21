// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class GETSTARTED_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		class UCameraComponent* FollowCamera;

	float BaseTurnRate;

	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Staus")
		float MaxHealth;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Staus")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Staus")
		float MaxStamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Staus")
		float Stamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Staus")
		int32 Coins;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void IncreaseHealth(float Value);

	void IncreaseStamina(float Value);

	void IncreaseCoins(int Value);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
