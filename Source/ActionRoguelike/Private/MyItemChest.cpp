// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"

// Sets default values
AMyItemChest::AMyItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMash;

	LidMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMash->SetupAttachment(BaseMash);

	TargetPitch = 120;
}

void AMyItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMash->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void AMyItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

