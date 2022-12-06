// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
  GENERATED_BODY()

protected:

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Pickup")
  float HealthAmount = 100.0f;

private:
  virtual bool GivePickUpTo(APawn *PlayerPawn) override;
};
