// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractionComponent.h"
#include "MyGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMyInteractionComponent::UMyInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* Owner = GetOwner();//** who use this interaction component

	FVector Start;
	FVector End;
	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	Start = EyeLocation;
	End = EyeLocation + (EyeRotation.Vector() * 500.0f);

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	float Radius = 70.0f;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);

	//** Debug
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			if (HitActor->Implements<UMyGameplayInterface>())
			{
				APawn* Pawn = Cast<APawn>(Owner);

				IMyGameplayInterface::Execute_Interact(HitActor, Pawn);

				//** Debug
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 8, LineColor, false, 2.0f, 0, 2.0f);

				break;
			}
		}
	}

	//** Debug
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, 0, 2.0f);
}

