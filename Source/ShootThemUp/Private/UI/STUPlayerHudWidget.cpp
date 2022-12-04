// Shoot Them Up. All right reserved.
#include "STUUtils.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "UI/STUPlayerHudWidget.h"

float USTUPlayerHudWidget::GetHealthPercent() const
{
  const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
  if (!HealthComponent) { return 0.0f; }

  return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHudWidget::GetWeaponUIData(FWeaponUIData &UIData) const
{
  const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
  if (!WeaponComponent) { return false; }

  return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHudWidget::GetWeaponAmmoData(FAmmoData &AmmoData) const
{
  const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
  if (!WeaponComponent) { return false; }

  return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHudWidget::IsPlayerAlive() const
{
  const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
  return HealthComponent && !HealthComponent->IsDead();
}
bool USTUPlayerHudWidget::IsPlayerSpectating() const
{
  const auto Controller = GetOwningPlayer();
  return Controller && Controller->GetStateName() == NAME_Spectating;
}