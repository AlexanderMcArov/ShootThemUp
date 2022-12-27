// Shoot Them Up. All right reserved.

#include "AI/EQS/STUNextToEnemyLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUNextToEnemyLocation::ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const
{
  AActor *QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

  const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
  if (!Blackboard) return;
  const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
  UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
