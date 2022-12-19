// Shoot Them Up. All right reserved.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "STUAIController.generated.h"

/**
 *
 */

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
  GENERATED_BODY()

public:
  ASTUAIController();

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
  USTUAIPerceptionComponent *STUAIPerceptionComponent;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
  FName FocusOnKeyName = "EnemyActor";

  virtual void OnPossess(APawn *InPawn) override;
  virtual void Tick(float DeltaTime) override;

private:
  AActor *GetFocusOnActor() const;
};
