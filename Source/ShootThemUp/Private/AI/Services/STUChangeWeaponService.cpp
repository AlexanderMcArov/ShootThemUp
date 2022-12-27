// Shoot Them Up. All right reserved.

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService() { NodeName = "Change Weapon"; }

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

  const auto Controller = OwnerComp.GetAIOwner();

  if (Controller)
  {
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

    if (WeaponComponent && FMath::Rand() <= Probability && Probability > 0)
    {
      WeaponComponent->NextWeapon();
    }
  }

  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
