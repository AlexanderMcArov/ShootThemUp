// Shoot Them Up. All right reserved.

#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "STUUtils.h"

AActor *USTUAIPerceptionComponent::GetClosestEnemy() const
{
  TArray<AActor *> PercieveActors;
  GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
  if (PercieveActors.Num() == 0) return nullptr;

  const auto Controller = Cast<AAIController>(GetOwner());
  if (!Controller) return nullptr;

  const auto Pawn = Controller->GetPawn();
  if (!Pawn) return nullptr;

  float   BestDistance = MAX_FLT;
  AActor *BestPawn     = nullptr;

  for (const auto PerciveActor : PercieveActors)
  {
    const auto HealthComponent = PerciveActor->FindComponentByClass<USTUHealthComponent>();
    if (HealthComponent && !HealthComponent->IsDead()) // TODO: Check if is enemy
    {
      const auto CurrentDistance = (PerciveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
      if (CurrentDistance < BestDistance)
      {
        BestDistance = CurrentDistance;
        BestPawn     = PerciveActor;
      }
    }
  }
  return BestPawn;
}
