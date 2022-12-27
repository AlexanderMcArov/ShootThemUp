// Shoot Them Up. All right reserved.

#include "AI/Services/STUFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

USTUFireService::USTUFireService() { NodeName = "Fire Service"; }

void USTUFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
  const auto Blackboard = OwnerComp.GetBlackboardComponent();
  const auto Controller = OwnerComp.GetAIOwner();

  const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

  if (Controller)
  {
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    UE_LOG(LogTemp, Warning, TEXT("WeaponComponent: %i"), WeaponComponent);
    if (WeaponComponent) { HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire(); }
  }
  Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
