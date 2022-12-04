// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"

#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
  GENERATED_BODY()

public:
  ASTUBaseWeapon();

  virtual void           StartFire();
  virtual void           StopFire();
  FOnClimpEmptySignature OnClimpEmpty;

  void ChangeClip();
  bool CanReload() const;

  FWeaponUIData GetUIData() const { return WeaponUIData; }
  FAmmoData     GetAmmoData() const { return CurrentAmmo; }

protected:
  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  USkeletalMeshComponent *WeaponMeshComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName MuzzleSocketName = "MuzzleFlashSocket";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float TraceMaxDistance = 1500.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FAmmoData DefaultAmmo{15, 10, false};

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponUI")
  FWeaponUIData WeaponUIData;

  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

  APlayerController *GetPlayerController() const;
  bool               GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
  FVector            GetMuzzleWorldLocation() const;
  void               MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);

  void DecreaseAmmo();
  bool IsAmmoEmpty() const;
  bool IsClipEmpty() const;

private:
  FAmmoData CurrentAmmo;
};
