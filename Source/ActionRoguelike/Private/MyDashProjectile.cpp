// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDashProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AMyDashProjectile::AMyDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.f;
}


// Called when the game starts or when spawned
void AMyDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyCharacter = this->GetInstigator();
	SphereComp->IgnoreActorWhenMoving(MyCharacter, true);

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AMyDashProjectile::Explode, DetonateDelay);
}

void AMyDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AMyDashProjectile::TeleportInstigator, TeleportDelay);
}

void AMyDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();

	FVector DashProjectileLocation = GetActorLocation();

	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(DashProjectileLocation, ActorToTeleport->GetActorRotation(), false, false);
	}

	Destroy();
}
