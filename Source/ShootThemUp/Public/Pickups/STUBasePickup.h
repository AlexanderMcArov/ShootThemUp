// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class UMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
  GENERATED_BODY()

public:
  ASTUBasePickup();
  virtual void Tick(float DeltaTime) override;

protected:
  UPROPERTY(VisibleAnyWhere, Category = "Pickup")
  USphereComponent *CollisionComponent;

  UPROPERTY(EditAnyWhere, Category = "Pickup")
  float RespawnTime = 5.0f;

  virtual void BeginPlay() override;
  virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

private:
  float RotationYaw = 0.0f;

  virtual bool GivePickUpTo(APawn *PlayerPawn);

  void PickupWasTaken();
  void Respawn();
  void GenerateRotationYaw();
};
