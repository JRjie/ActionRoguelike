#pragma once

#include "CoreMinimal.h"
#include "MyProjectileBase.h"
#include "MyCharacter.h"
#include "MyMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AMyMagicProjectile : public AMyProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyMagicProjectile();

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

//public:
//
//	virtual void Tick(float DeltaTime) override;
};