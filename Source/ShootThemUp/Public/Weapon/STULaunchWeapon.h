// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"

#include "STULaunchWeapon.generated.h"

class ASTUProjectile;

UCLASS()
class SHOOTTHEMUP_API ASTULaunchWeapon : public ASTUBaseWeapon
{
  GENERATED_BODY()

public:
  virtual void StartFire() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TSubclassOf<ASTUProjectile> ProjectileClass;

  virtual void MakeShot();
};
