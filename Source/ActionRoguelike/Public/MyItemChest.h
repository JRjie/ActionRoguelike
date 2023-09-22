// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameplayInterface.h"
#include "Components/TimelineComponent.h"
#include "MyItemChest.generated.h"

class UStaticMeshComponent;//** Added Header file on .cpp
class UTimelineComponent;

UCLASS()
class ACTIONROGUELIKE_API AMyItemChest : public AActor, public IMyGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn) override; //C++ implementation of the interface function

public:	
	// Sets default values for this actor's properties
	AMyItemChest();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GoldensMash;

	//** animation
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTimelineComponent* AnimateLidComp;

	FOnTimelineFloat AnimateLidFunc;

	UPROPERTY(EditAnywhere)
	UCurveFloat* LidOpenCurve;

	UPROPERTY(EditAnywhere)
	UCurveFloat* LidCloseCurve;

	UFUNCTION()
	void UpdateLidPitch(float Pitch);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
