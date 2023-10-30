#include "MyAttributeComponent.h"

UMyAttributeComponent::UMyAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = 100.0f;
}


bool UMyAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UMyAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

