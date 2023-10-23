// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTargetDummy.h"
#include "MyAttributeComponent.h"

// Sets default values
AMyTargetDummy::AMyTargetDummy()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>(TEXT("AttributeComp"));
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMyTargetDummy::OnHealthChanged);
}

void AMyTargetDummy::OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}
     