// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
  GENERATED_BODY()

public:
  ASTUProjectile();

  void SetShotDirection(const FVector &Direction)
  {
    ShotDirection = Direction;
  }

protected:
  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  USphereComponent *CollisionComponent;

  UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
  UProjectileMovementComponent *MovementComponent;

  UPROPERTY(VisibleAnyWhere, Category = "VFX")
  USTUWeaponFXComponent *WeaponFXComponent;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float DamageRadius = 200.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float DamageAmount = 50.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  bool DoFullDamage = false;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
  float LifeSeconds = 5.0;

  virtual void BeginPlay() override;

private:
  FVector ShotDirection;

  UFUNCTION()
  void OnProjectileHit(
      UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse,
      const FHitResult &Hit
  );

  AController *GetController() const;
};
