#pragma once

#include "CoreMinimal.h"
#include "MyProjectileBase.h"
#include "MyCharacter.h"
#include "MyDashProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API AMyDashProjectile : public AMyProjectileBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyDashProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DelayedDetonate;

	void TeleportInstigator();

	virtual void Explode_Implementation() override;

	virtual void BeginPlay() override;

//public:
//
//	virtual void Tick(float DeltaTime) override;
};
