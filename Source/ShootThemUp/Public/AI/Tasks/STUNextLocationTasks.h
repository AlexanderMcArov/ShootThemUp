// Shoot Them Up. All right reserved.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"
#include "STUNextLocationTasks.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTasks : public UBTTaskNode
{
  GENERATED_BODY()
public:
  USTUNextLocationTasks();

  virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

protected:
  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
  float Radius = 1000.0f;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
  FBlackboardKeySelector AimLocationKey;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
  bool SelfCenter = true;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
  FBlackboardKeySelector CenterActorKey;
};
