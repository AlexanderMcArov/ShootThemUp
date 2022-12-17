// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"

#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
  GENERATED_BODY()

public:
  ASTURifleWeapon();

  virtual void StartFire() override;
  virtual void StopFire() override;

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float TimeBetweenShots = 0.1f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float BulletSpread = 1.5f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float DamageAmount = 7.5f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UNiagaraSystem *TraceEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  FString TraceTargetName = "TraceTarget";

  UPROPERTY(VisibleAnyWhere, Category = "VFX")
  USTUWeaponFXComponent *WeaponFXComponent;

  virtual void BeginPlay() override;
  virtual void MakeShot() override;
  virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;

private:
  UPROPERTY()
  UNiagaraComponent *MuzzleEffectComponent;

  FTimerHandle ShotTimerHandle;

  void MakeDamage(const FHitResult &HitResult);
  void InitMuzzleFX();
  void SetMuzzleFXVisiblility(bool Visible);
  void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);
};
