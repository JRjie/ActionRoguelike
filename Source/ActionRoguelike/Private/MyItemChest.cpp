// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyItemChest::AMyItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMash;

	LidMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMash->SetupAttachment(BaseMash);

	GoldensMash = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoldensMesh"));
	GoldensMash->SetupAttachment(BaseMash);

	AnimateLidComp = CreateDefaultSubobject<UTimelineComponent>("AnimateLidComp");
}

void AMyItemChest::UpdateLidPitch(float Pitch)
{
	LidMash->SetRelativeRotation(FRotator(Pitch, 0.0f, 0.0f));
}

void AMyItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	if (AnimateLidComp->IsPlaying() == true)
	{
		return;
	}
	else{
		FRotator LidRotator = LidMash->GetRelativeRotation();
		float LidPitch = LidRotator.Pitch;

		if (LidPitch == 0.0f && LidOpenCurve)
		{
			AnimateLidFunc.BindDynamic(this, &AMyItemChest::UpdateLidPitch);
			AnimateLidComp->AddInterpFloat(LidOpenCurve, AnimateLidFunc, FName("LidPitch"));
			AnimateLidComp->SetNewTime(0.0);
			AnimateLidComp->Play();
		}

		else if (LidPitch == 60.0f && LidCloseCurve)
		{
			AnimateLidFunc.BindDynamic(this, &AMyItemChest::UpdateLidPitch);
			AnimateLidComp->AddInterpFloat(LidCloseCurve, AnimateLidFunc, FName("LidPitch"));
			AnimateLidComp->SetNewTime(0.0);
			AnimateLidComp->Play();
		}
	}
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

