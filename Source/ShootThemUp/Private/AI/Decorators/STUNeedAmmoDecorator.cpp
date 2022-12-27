// Shoot Them Up. All right reserved.

#include "AI/Decorators/STUNeedAmmoDecorator.h"
#include "AIcontroller.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator() { NodeName = "Need Ammo"; }

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
  const auto Controller = OwnerComp.GetAIOwner();
  if (!Controller) return false;

  const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
  if (!WeaponComponent) return false;

  return WeaponComponent->IsNeedAmmoForAnyWeapon(WeaponType);
}
