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

	virtual void BeginPlay() override;

//public:
//
//	virtual void Tick(float DeltaTime) override;
};