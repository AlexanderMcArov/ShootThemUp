// Shoot Them Up. All right reserved.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
  PrimaryActorTick.bCanEverTick = false;

  CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
  CollisionComponent->InitSphereRadius(5.0f);
  CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
  CollisionComponent->bReturnMaterialOnMove = true;
  SetRootComponent(CollisionComponent);

  MovementComponent               = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
  MovementComponent->InitialSpeed = 2000.0f;

  WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::BeginPlay()
{
  Super::BeginPlay();
  check(MovementComponent);
  check(CollisionComponent);
  check(WeaponFXComponent);

  MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
  CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
  SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
  UE_LOG(LogTemp, Warning, TEXT("HITHIT"));
  MovementComponent->StopMovementImmediately();
  UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount,         //
                                      GetActorLocation(), DamageRadius, //
                                      UDamageType::StaticClass(),       //
                                      {}, this,                         //
                                      GetController(), DoFullDamage);
  DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, LifeSeconds);
  WeaponFXComponent->PlayImpactFX(Hit);
  Destroy();
}

AController *ASTUProjectile::GetController() const
{
  const auto Pawn = Cast<APawn>(GetOwner());
  return Pawn ? Pawn->GetController() : nullptr;
}
