// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

class ASTUBaseWeapon;
/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
  GENERATED_BODY()

protected:
  UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
  int32 ClipsAmount = 10;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
  TSubclassOf<ASTUBaseWeapon> WeaponType;

private:
  virtual bool GivePickUpTo(APawn *PlayerPawn) override;
};
