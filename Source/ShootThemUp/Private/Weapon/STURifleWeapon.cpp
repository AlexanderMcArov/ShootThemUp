// Shoot Them Up. All right reserved.

#include "Weapon/STURifleWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
  WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
  Super::BeginPlay();
  check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
  InitMuzzleFX();
  GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, true);
  MakeShot();
}

void ASTURifleWeapon::StopFire()
{
  SetMuzzleFXVisiblility(false);
  GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
  if (!GetWorld() || IsAmmoEmpty()) return StopFire();

  FVector TraceStart, TraceEnd;
  if (!GetTraceData(TraceStart, TraceEnd)) return StopFire();

  FHitResult HitResult;
  MakeHit(HitResult, TraceStart, TraceEnd);

  FVector TraceEndFX = TraceEnd;
  if (HitResult.bBlockingHit)
  {
    WeaponFXComponent->PlayImpactFX(HitResult);
    MakeDamage(HitResult);
    TraceEndFX = HitResult.ImpactPoint;
  }

  SpawnTraceFX(GetMuzzleWorldLocation(), TraceEndFX);
  DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
  FVector  ViewLocation;
  FRotator ViewRotation;
  if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

  TraceStart                   = ViewLocation;
  const auto    HalfRad        = FMath::DegreesToRadians(BulletSpread);
  const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
  TraceEnd                     = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult &HitResult)
{
  const auto DamageActor = HitResult.GetActor();
  if (!DamageActor) return;
  const auto Player = Cast<ACharacter>(GetOwner());
  if (!Player) return;

  const auto Controller = Player->GetController<APlayerController>();

  DamageActor->TakeDamage(DamageAmount, FDamageEvent{}, Controller, DamageActor);
}

void ASTURifleWeapon::InitMuzzleFX()
{
  if (!MuzzleEffectComponent) { MuzzleEffectComponent = SpawnMuzzleFX(); }
  SetMuzzleFXVisiblility(true);
}

void ASTURifleWeapon::SetMuzzleFXVisiblility(bool Visible)
{
  if (MuzzleEffectComponent)
  {
    MuzzleEffectComponent->SetPaused(!Visible);
    MuzzleEffectComponent->SetVisibility(Visible, true);
  }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd)
{
  const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation( //
      GetWorld(),                                                               //
      TraceEffect,                                                              //
      TraceStart);
  UE_LOG(LogTemp, Warning, TEXT("%s"), *TraceEnd.ToString());
  if (TraceFXComponent) { TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd); }
}
