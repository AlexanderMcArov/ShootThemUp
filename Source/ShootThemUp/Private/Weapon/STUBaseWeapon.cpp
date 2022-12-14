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
}

void ASTUBaseWeapon::StartFire()
{
  UE_LOG(LogTemp, Warning, TEXT("BaseWeapon"));
}

void ASTUBaseWeapon::StopFire()
{
}

void ASTUBaseWeapon::MakeShot()
{
  
}



bool ASTUBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
  const auto Controller = GetPlayerController();
  if (!Controller)
    return false;

  Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
  return true;
}

bool ASTUBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
  FVector ViewLocation;
  FRotator ViewRotation;
  if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
    return false;

  TraceStart = ViewLocation;
  const FVector ShootDirection = ViewRotation.Vector();
  TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
  return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
  return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

APlayerController *ASTUBaseWeapon::GetPlayerController() const
{
  const auto Player = Cast<ACharacter>(GetOwner());
  if (!Player)
    return nullptr;

  return Player->GetController<APlayerController>();
}

void ASTUBaseWeapon::MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd)
{
  if (!GetWorld())
    return;

  FCollisionQueryParams CollisionParams;
  CollisionParams.AddIgnoredActor(GetOwner());

  GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}