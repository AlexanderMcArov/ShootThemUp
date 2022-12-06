// Shoot Them Up. All right reserved.

#include "Pickups/STUAmmoPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

bool ASTUAmmoPickup::GivePickUpTo(APawn *PlayerPawn)
{

  const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
  if (!HealthComponent || HealthComponent->IsDead()) return false;

  const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
  if (!WeaponComponent) return false;

  return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
