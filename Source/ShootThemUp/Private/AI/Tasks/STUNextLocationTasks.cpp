// Shoot Them Up. All right reserved.

#include "AI/Tasks/STUNextLocationTasks.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

USTUNextLocationTasks::USTUNextLocationTasks() { NodeName = "Next Location"; }

EBTNodeResult::Type USTUNextLocationTasks::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
  const auto Controller = OwnerComp.GetAIOwner();
  const auto BlackBoard = OwnerComp.GetBlackboardComponent();
  if (!Controller || !BlackBoard) return EBTNodeResult::Failed;

  const auto Pawn = Controller->GetPawn();
  if (!Pawn) return EBTNodeResult::Failed;

  const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
  if (!NavSys) return EBTNodeResult::Failed;

  FNavLocation NavLocation;

  auto Location = Pawn->GetActorLocation();

  if (!SelfCenter)
  {
    auto CenterActor = Cast<AActor>(BlackBoard->GetValueAsObject(CenterActorKey.SelectedKeyName));
    if (!CenterActor) return EBTNodeResult::Failed;
    Location = CenterActor->GetActorLocation();
  }

  const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
  if (!Found) return EBTNodeResult::Failed;

  BlackBoard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
  return EBTNodeResult::Succeeded;
}
