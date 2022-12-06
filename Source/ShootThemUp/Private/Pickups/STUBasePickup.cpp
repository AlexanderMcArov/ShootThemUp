// Shoot Them Up. All right reserved.

#include "Pickups/STUBasePickup.h"
#include "Components/MeshComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
  PrimaryActorTick.bCanEverTick = true;

  CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
  CollisionComponent->InitSphereRadius(50.0f);
  CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
  Super::BeginPlay();
  GenerateRotationYaw();
  check(CollisionComponent);
}

void ASTUBasePickup::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
  UE_LOG(LogBasePickup, Warning, TEXT("Bullet"));
  Super::NotifyActorBeginOverlap(OtherActor);
  const auto Pawn = Cast<APawn>(OtherActor);
  if (!Pawn) return;
  if (GivePickUpTo(Pawn)) PickupWasTaken();
}

void ASTUBasePickup::PickupWasTaken()
{
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  GetRootComponent()->SetVisibility(false, true);

  FTimerHandle RespawnTimerHandle;
  GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
  CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  GetRootComponent()->SetVisibility(true, true);
}

void ASTUBasePickup::GenerateRotationYaw()
{
  const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;

  RotationYaw = FMath::RandRange(1.0f, 2.0f) + Direction;
}

bool ASTUBasePickup::GivePickUpTo(APawn *PlayerPawn) { return true; }
