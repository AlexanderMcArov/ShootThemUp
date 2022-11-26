// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
  GENERATED_BODY()

public:
  ASTUBaseWeapon();

  virtual void StartFire();
  virtual void StopFire();

protected:
  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  USkeletalMeshComponent *WeaponMeshComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName MuzzleSocketName = "MuzzleFlashSocket";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  float TraceMaxDistance = 1500.0f;

  virtual void BeginPlay() override;
  virtual void MakeShot();
  virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

  APlayerController *GetPlayerController() const;
  bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
  FVector GetMuzzleWorldLocation() const;
  void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);

private:
};
