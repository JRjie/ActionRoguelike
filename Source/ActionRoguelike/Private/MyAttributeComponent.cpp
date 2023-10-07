#include "MyAttributeComponent.h"

UMyAttributeComponent::UMyAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = 100.0f;
}

bool UMyAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	return true;
}

