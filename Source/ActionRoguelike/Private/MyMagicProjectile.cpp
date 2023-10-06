#include "MyMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AMyMagicProjectile::AMyMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyCharacter = this->GetInstigator();
	SphereComp->IgnoreActorWhenMoving(MyCharacter, true);
}

// Called every frame
//void AMyMagicProjectile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}