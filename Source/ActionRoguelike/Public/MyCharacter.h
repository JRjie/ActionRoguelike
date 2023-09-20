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

UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;//** safe UClass

protected:

	UPROPERTY(VisibleAnywhere)//exposure all variable
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//** Keyboard Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveTransverseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveJumpAction;

	//** Mouse Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputMappingContext* IM_MouseMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseXAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseYAction;

	//** Skill trigger Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard|Skill", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_SkillMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard|Skill", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill1Action;

	//** Interaction Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard|Interaction", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_InteractionMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keyboard|Interaction", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_InteractAction;

	//** 
	UPROPERTY(VisibleAnywhere)
	UMyInteractionComponent* InteractionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//MoveFunction
	void MoveForward(const FInputActionValue& InputValue);
	void MoveTransverse(const FInputActionValue& InputValue);
	void MoveJump(const FInputActionValue& InputValue);

	void MoveMouseX(const FInputActionValue& InputValue);
    void MoveMouseY(const FInputActionValue& InputValue);

	void Skill1();

	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
