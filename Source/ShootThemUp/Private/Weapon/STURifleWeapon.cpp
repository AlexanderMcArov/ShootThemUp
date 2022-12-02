// Shoot Them Up. All right reserved.

#include "Weapon/STURifleWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

void ASTURifleWeapon::StartFire()
{
  GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
  MakeShot();
}

void ASTURifleWeapon::StopFire()
{
  GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
  if (!GetWorld() || IsAmmoEmpty())
    return StopFire();

  FVector TraceStart, TraceEnd;
  if (!GetTraceData(TraceStart, TraceEnd))
    return StopFire();

  FHitResult HitResult;
  MakeHit(HitResult, TraceStart, TraceEnd);

  if (HitResult.bBlockingHit)
  {
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
    DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

    MakeDamage(HitResult);
  }
  else
  {
    DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Blue, false, 3.0f, 0, 3.0f);
  }

  DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
  FVector ViewLocation;
  FRotator ViewRotation;
  if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    return false;

  TraceStart = ViewLocation;
  const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
  const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
  TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult &HitResult)
{
  const auto DamageActor = HitResult.GetActor();
  if (!DamageActor)
    return;
  const auto Player = Cast<ACharacter>(GetOwner());
  if (!Player)
    return;

  const auto Controller = Player->GetController<APlayerController>();

  DamageActor->TakeDamage(5.0f, FDamageEvent{}, Controller, DamageActor);
}