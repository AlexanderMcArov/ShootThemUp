// Shoot Them Up. All right reserved.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "STUHealthPercentDecorator.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUHealthPercentDecorator : public UBTDecorator
{
  GENERATED_BODY()

public:
  USTUHealthPercentDecorator();

protected:
  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
  float HealthPercent = 0.6f;

  virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
