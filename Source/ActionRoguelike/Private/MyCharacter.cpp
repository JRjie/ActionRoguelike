 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"

#include "GameFramework\CharacterMovementComponent.h"
#include "MyInteractionComponent.h"

#include "Math/RotationTranslationMatrix.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UMyInteractionComponent>("InteractionComp");

	//** allow the Camera & SpringArm to use Pawn Control Rotation
	CameraComp->bUsePawnControlRotation = true;
	SpringArmComp->bUsePawnControlRotation = true;
	//** decoupling Camera Yaw & Figure Pawn Yaw
	this->bUseControllerRotationYaw = false;
	//** allow figure to rotate
	GetCharacterMovement()->bOrientRotationToMovement = true;
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
			Subsystem->AddMappingContext(IM_SkillMappingContext, 0);
			Subsystem->AddMappingContext(IM_InteractionMappingContext, 0);
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
		const FRotator Rotation = Controller->GetControlRotation();
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
		const FRotator Rotation = Controller->GetControlRotation();
		//** set the flat coordinate:{x, y}
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//** find the direction of forward
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//** control to move
		AddMovementInput(Direction, value);
	}

}


//void AMyCharacter::MoveJump(const FInputActionValue& InputValue)
//{
//	float value = InputValue.GetMagnitude();
//	if (Controller != nullptr)
//	{
//		//TODO
//	}
//}


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


void AMyCharacter::PrimaryAttack()
{
		PlayAnimMontage(AttackAnim);

		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMyCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void AMyCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(MagicProjectileClass);
}


void AMyCharacter::Dash()
{
		PlayAnimMontage(AttackAnim);

		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMyCharacter::Dash_TimeElapsed, 0.2f);
}

void AMyCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}


void AMyCharacter::SpawnProjectile(TSubclassOf<AActor> ProjectileClass)
{
	if (ensure(ProjectileClass))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		//** allow skill pawn to spawn when it is overlapping with other pawns
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FVector Start = CameraComp->GetComponentLocation();

		FVector End = Start + (GetControlRotation().Vector() * 50000.0f);

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, ObjParams, Shape, Params))
		{
			End = Hit.ImpactPoint;
		}

		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(End - HandLocation).Rotator();

		//** get the SpringArm Rotation:{pitch, yaw, roll}
		FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}


void AMyCharacter::PrimaryInteract()
{
	if (Controller != nullptr && InteractionComp != nullptr)
	{
		InteractionComp->PrimaryInteract();
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
		EnhancedInputComponent->BindAction(IA_MoveJumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);

		EnhancedInputComponent->BindAction(IA_MoveMouseXAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveMouseX);
		EnhancedInputComponent->BindAction(IA_MoveMouseYAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveMouseY);

		EnhancedInputComponent->BindAction(IA_Skill1Action, ETriggerEvent::Triggered, this, &AMyCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(IA_Skill2Action, ETriggerEvent::Triggered, this, &AMyCharacter::Dash);

		EnhancedInputComponent->BindAction(IA_InteractAction, ETriggerEvent::Triggered, this, &AMyCharacter::PrimaryInteract);
	}
}

