// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;

class UMyInteractionComponent;

class UAnimMontage;

class UMyAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MagicProjectileClass;//** safe UClass

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DashProjectileClass;//** safe UClass

	UPROPERTY(VisibleAnywhere)//exposure all variable
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMyInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMyAttributeComponent* AttributeComp;

protected:

	//** Keyboard Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Move", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Move", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Move", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveTransverseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Move", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveJumpAction;


	//** Mouse Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|View", meta = (AllowPrivareAccess ="true"))
	UInputMappingContext* IM_MouseMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|View", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseXAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|View", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseYAction;


	//** Skill trigger Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|Skill", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_SkillMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|Skill", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill1Action;//** MagicProjectile

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse|Skill", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill2Action;//** DashProjectile

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim|Attack", meta = (AllowPrivateAccess = "ture"))
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;


	//** Interaction Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Interaction", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_InteractionMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Keyboard|Interaction", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_InteractAction;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//** MoveFunction
	void MoveForward(const FInputActionValue& InputValue);
	void MoveTransverse(const FInputActionValue& InputValue);
	//void MoveJump(const FInputActionValue& InputValue);

	void MoveMouseX(const FInputActionValue& InputValue);
    void MoveMouseY(const FInputActionValue& InputValue);

	void SpawnProjectile(TSubclassOf<AActor> ProjectileClass);
	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void Dash();
	void Dash_TimeElapsed();

	void PrimaryInteract();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//** Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
