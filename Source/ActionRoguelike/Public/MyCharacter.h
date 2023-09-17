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

UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:

	UPROPERTY(VisibleAnywhere)//exposure all variable
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keybord", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IM_DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keybord", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keybord", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveTransverseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Keybord", meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MoveJumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputMappingContext* IM_MouseMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseXAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerAction|Input|Mouse", meta = (AllowPrivareAccess ="true"))
	UInputAction* IA_MoveMouseYAction;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//MoveFunction
	void MoveForward(const FInputActionValue& InputValue);
	void MoveTransverse(const FInputActionValue& InputValue);
	void MoveJump(const FInputActionValue& InputValue);
	void MoveMouseX(const FInputActionValue& InputValue);
    void MoveMouseY(const FInputActionValue& InputValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
