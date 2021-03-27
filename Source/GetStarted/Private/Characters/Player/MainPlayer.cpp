// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MainPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCapsuleSize(35.0f, 100.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.15f;

	BaseTurnRate = 65.0f;
	BaseLookUpRate = 65.0f;

	MaxHealth = 100.0f;
	Health = MaxHealth;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	Coins = 0;

	StaminaConsumeRate = 20.0f;
	ExhaustedStaminaRatio = 0.167f;
	PlayerStaminaStatus = EPlayerStaminaStatus::EPSS_Normal;

	RunningSpeed = 600.0f;
	SprintingSpeed = 900.0f;
	PlayerMovementStatus = EPlayerMovementStatus::EPMS_Normal;

	bLeftShiftKeyDown = false;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (PlayerStaminaStatus)
	{
		case EPlayerStaminaStatus::EPSS_Normal:
			if (bLeftShiftKeyDown)
			{
				if (Stamina - StaminaConsumeRate * DeltaTime <= MaxStamina * ExhaustedStaminaRatio)
				{
					PlayerStaminaStatus = EPlayerStaminaStatus::EPSS_Exhausted;
				}
				Stamina -= StaminaConsumeRate * DeltaTime;
				SetPlayerMovementStatus(EPlayerMovementStatus::EPMS_Sprinting);
			}
			else
			{
				Stamina = FMath::Clamp(Stamina + StaminaConsumeRate * DeltaTime, 0.0f, MaxStamina);
			}
			break;
		case EPlayerStaminaStatus::EPSS_Exhausted:
			if (bLeftShiftKeyDown)
			{
				if (Stamina - StaminaConsumeRate * DeltaTime <= 0.0f)
				{
					PlayerStaminaStatus = EPlayerStaminaStatus::EPSS_ExhaustedRecovering;
					LeftShiftKeyUp();
					SetPlayerMovementStatus(EPlayerMovementStatus::EPMS_Normal);
				}
				else
				{
					Stamina -= StaminaConsumeRate * DeltaTime;
				}
			}
			else
			{
				PlayerStaminaStatus = EPlayerStaminaStatus::EPSS_ExhaustedRecovering;
				Stamina = FMath::Clamp(Stamina + StaminaConsumeRate * DeltaTime, 0.0f, MaxStamina);
				SetPlayerMovementStatus(EPlayerMovementStatus::EPMS_Normal);
			}
			break;
		case EPlayerStaminaStatus::EPSS_ExhaustedRecovering:
			if (Stamina + StaminaConsumeRate * DeltaTime >= MaxStamina * ExhaustedStaminaRatio)
			{
				PlayerStaminaStatus = EPlayerStaminaStatus::EPSS_Normal;
			}
			Stamina += StaminaConsumeRate * DeltaTime;
			LeftShiftKeyUp();
			SetPlayerMovementStatus(EPlayerMovementStatus::EPMS_Normal);
			break;
		default:
			break;
	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainPlayer::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMainPlayer::LeftShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMainPlayer::LeftShiftKeyUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMainPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayer::LookUp);

	PlayerInputComponent->BindAxis("TurnAtRate", this, &AMainPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AMainPlayer::LookUpAtRate);
}

void AMainPlayer::Jump()
{
	Super::Jump();
}

void AMainPlayer::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayer::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayer::Turn(float Value)
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AMainPlayer::LookUp(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Value/*GetControlRotation().Pitch*/);
	if (GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch > 180.0f && Value > 0.0f)
	{
		return;
	}
	if (GetControlRotation().Pitch > 45.0f && GetControlRotation().Pitch < 180.0f && Value < 0.0f)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void AMainPlayer::TurnAtRate(float Rate)
{
	float Value = Rate * BaseTurnRate * GetWorld()->DeltaTimeSeconds;
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

void AMainPlayer::LookUpAtRate(float Rate)
{
	float Value = Rate * BaseLookUpRate * GetWorld()->DeltaTimeSeconds;
	if (GetControlRotation().Pitch < 270.0f && GetControlRotation().Pitch > 180.0f && Value > 0.0f)
	{
		return;
	}
	if (GetControlRotation().Pitch > 45.0f && GetControlRotation().Pitch < 180.0f && Value < 0.0f)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void AMainPlayer::IncreaseHealth(float Value)
{
	Health = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
}

void AMainPlayer::IncreaseStamina(float Value)
{
	Stamina = FMath::Clamp(Stamina + Value, 0.0f, MaxStamina);
}

void AMainPlayer::IncreaseCoins(int Value)
{
	Coins += Value;
}

float AMainPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health - Damage <= 0.0f)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	}
	else
	{
		Health -= Damage;
	}
	return Health;
}

void AMainPlayer::SetPlayerMovementStatus(EPlayerMovementStatus status)
{
	PlayerMovementStatus = status;

	switch (status)
	{
		case EPlayerMovementStatus::EPMS_Sprinting:
			GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
			break;
		default:
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			break;
	}
}

