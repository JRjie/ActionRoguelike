 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	//** allow the pawn to control the camera rotation
	CameraComp->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//** Get the EnhancedInputLocalPlayerSubsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IM_DefaultMappingContext, 0);
			Subsystem->AddMappingContext(IM_MouseMappingContext, 0);
		}
	}
}

//** MoveFunction
void AMyCharacter::MoveForward(const FInputActionValue &InputValue)
{
	float value = InputValue.GetMagnitude();
	
	if (Controller != nullptr && value != 0.0f)
	{
		//** get the SpringArm Rotation:{x, y, z}
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Rotation = GetViewRotation();
		//** set the flat coordinate:{x, y}
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//** find the direction of forward
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		//** control to move
		AddMovementInput(Direction, value);
	}
}

void AMyCharacter::MoveTransverse(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();

	if (Controller != nullptr && value != 0.0f)
	{
		//** get the SpringArm Rotation:{pitch, yaw, roll}
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Rotation = GetViewRotation();
		//** set the flat coordinate:{x, y}
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//** find the direction of forward
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//** control to move
		AddMovementInput(Direction, value);
	}

}

void AMyCharacter::MoveJump(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();
	if (Controller != nullptr)
	{

	}
}

void AMyCharacter::MoveMouseX(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();
	if (Controller != nullptr)
	{
		AddControllerYawInput(value * 0.7);
	}
}

void AMyCharacter::MoveMouseY(const FInputActionValue& InputValue)
{
	float value = InputValue.GetMagnitude();
	if (Controller != nullptr)
	{
		AddControllerPitchInput(value * 0.7);
	}
}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//** Bind the action
		EnhancedInputComponent->BindAction(IA_MoveForwardAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForward);
		EnhancedInputComponent->BindAction(IA_MoveTransverseAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveTransverse);
		EnhancedInputComponent->BindAction(IA_MoveJumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveJump);
		EnhancedInputComponent->BindAction(IA_MoveMouseXAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveMouseX);
		EnhancedInputComponent->BindAction(IA_MoveMouseYAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveMouseY);
	}
}

