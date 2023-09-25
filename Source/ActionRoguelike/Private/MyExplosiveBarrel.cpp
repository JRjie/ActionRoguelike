// Fill out your copyright notice in the Description page of Project Settings.


#include "MyExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"
#include "MyMagicProjectile.h"

// Sets default values
AMyExplosiveBarrel::AMyExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp=CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 500.0f;//** 200000.0f if bImuplseVelChange = true

	ForceComp->bImpulseVelChange = true;

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void AMyExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentHit.AddDynamic(this, &AMyExplosiveBarrel::OnActorHit);
}

void AMyExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AMyMagicProjectile>(OtherActor))
	{
		ForceComp->FireImpulse();
	}
	else {
		return;
	}
	//** Debug
	//UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	//FString ComebinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	//DrawDebugString(GetWorld(), Hit.ImpactPoint, ComebinedString, nullptr, FColor::Green, 2.0f, true);
}

// Called every frame
void AMyExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

