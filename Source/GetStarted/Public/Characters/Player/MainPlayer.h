// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UENUM(BlueprintType)
enum class EPlayerMovementStatus :uint8
{
	EPMS_Normal  UMETA(DisplayName = "Normal"),
	EPMS_Sprinting	UMETA(DisplayName = "Sprinting"),
	EPMS_Dead	UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EPlayerStaminaStatus :uint8
{
	EPSS_Normal  UMETA(DisplayName = "Normal"),
	EPSS_Exhausted	UMETA(DisplayName = "Exhausted"),
	EPSS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering")
};


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

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Status")
		float StaminaConsumeRate;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Status")
		float ExhaustedStaminaRatio;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Status")
		EPlayerStaminaStatus PlayerStaminaStatus;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Status")
		float RunningSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Status")
		float SprintingSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Status")
		EPlayerMovementStatus PlayerMovementStatus;

	bool bLeftShiftKeyDown;

	bool bHasWeapon;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapon")
		class AWeaponItem* EquippedWeapon;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Weapon")
		class AWeaponItem* OverLappingWeapon;

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

	UFUNCTION(BlueprintCallable)
		void IncreaseHealth(float Value);

	UFUNCTION(BlueprintCallable)
		void IncreaseStamina(float Value);

	UFUNCTION(BlueprintCallable)
		void IncreaseCoins(int Value);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE void LeftShiftKeyDown() { bLeftShiftKeyDown = true; }

	FORCEINLINE void LeftShiftKeyUp() { bLeftShiftKeyDown = false; }

	void SetPlayerMovementStatus(EPlayerMovementStatus status);
};
