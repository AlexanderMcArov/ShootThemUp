// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STUNextToEnemyLocation.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUNextToEnemyLocation : public UEnvQueryContext
{
  GENERATED_BODY()

public:
  virtual void ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const override;

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  FName EnemyActorKeyName = "EnemyActor";
};
