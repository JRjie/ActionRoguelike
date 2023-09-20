// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameplayInterface.h"
#include "MyItemChest.generated.h"

class UStaticMeshComponent;//** Added Header file on .cpp

UCLASS()
class ACTIONROGUELIKE_API AMyItemChest : public AActor, public IMyGameplayInterface
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn) override; //C++ implementation of the interface function

public:	
	// Sets default values for this actor's properties
	AMyItemChest();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMash;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMash;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
