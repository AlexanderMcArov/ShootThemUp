// Shoot Them Up. All right reserved.

#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::GivePickUpTo(APawn *PlayerPawn)
{
  const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
  if (!HealthComponent) return false;

  return HealthComponent->TryToAddHealth(HealthAmount);
}
