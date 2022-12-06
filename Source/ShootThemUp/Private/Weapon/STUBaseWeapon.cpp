// Shoot Them Up. All right reserved.

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{

  PrimaryActorTick.bCanEverTick = false;

  WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
  SetRootComponent(WeaponMeshComponent);
}

void ASTUBaseWeapon::BeginPlay()
{
  Super::BeginPlay();
  CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::StartFire() { UE_LOG(LogTemp, Warning, TEXT("BaseWeapon")); }

void ASTUBaseWeapon::StopFire() {}

void ASTUBaseWeapon::MakeShot() {}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
  const auto Controller = GetPlayerController();
  if (!Controller) return false;

  Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
  return true;
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
  FVector  ViewLocation;
  FRotator ViewRotation;
  if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

  TraceStart                   = ViewLocation;
  const FVector ShootDirection = ViewRotation.Vector();
  TraceEnd                     = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
  return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

APlayerController *ASTUBaseWeapon::GetPlayerController() const
{
  const auto Player = Cast<ACharacter>(GetOwner());
  if (!Player) return nullptr;

  return Player->GetController<APlayerController>();
}

void ASTUBaseWeapon::MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd)
{
  if (!GetWorld()) return;

  FCollisionQueryParams CollisionParams;
  CollisionParams.AddIgnoredActor(GetOwner());

  GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
  if (CurrentAmmo.Bullets == 0) return;

  CurrentAmmo.Bullets--;

  if (IsClipEmpty() && !IsAmmoEmpty())
  {
    StopFire();
    OnClimpEmpty.Broadcast(this);
  }
}

void ASTUBaseWeapon::ChangeClip()
{
  if (!CurrentAmmo.Infinite)
  {
    if (CurrentAmmo.Clips == 0) return;

    CurrentAmmo.Clips--;
  }
  CurrentAmmo.Bullets = DefaultAmmo.Bullets;
  UE_LOG(LogBaseWeapon, Warning, TEXT("------ Change Clip ------"));
}

bool ASTUBaseWeapon::IsAmmoEmpty() const { return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty(); }
bool ASTUBaseWeapon::CanReload() const { return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0; }
bool ASTUBaseWeapon::IsClipEmpty() const { return CurrentAmmo.Bullets == 0; }
bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
  if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

  if (IsAmmoEmpty())
  {
    CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
    OnClimpEmpty.Broadcast(this);
  }
  else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
  {
    const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
    if (DefaultAmmo.Clips - NextClipsAmount >= 0) { CurrentAmmo.Clips = NextClipsAmount; }
    else
    {
      CurrentAmmo.Clips   = DefaultAmmo.Clips;
      CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
  }
  else
  {
    CurrentAmmo.Clips   = DefaultAmmo.Clips;
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
  }
  return true;
}

bool ASTUBaseWeapon::IsAmmoFull() const
{
  return CurrentAmmo.Bullets == DefaultAmmo.Bullets //
         && CurrentAmmo.Clips == DefaultAmmo.Clips;
}
