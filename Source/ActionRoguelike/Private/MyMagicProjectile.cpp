#include "MyMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyAttributeComponent.h"

AMyMagicProjectile::AMyMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMyMagicProjectile::OnActorOverlap);
}

void AMyMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(OtherActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AMyMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyCharacter = this->GetInstigator();
	SphereComp->IgnoreActorWhenMoving(MyCharacter, true);
}
