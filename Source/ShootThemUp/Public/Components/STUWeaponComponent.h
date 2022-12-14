// Shoot Them Up. All right reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  USTUWeaponComponent();

  void StartFire();
  void StopFire();
  void NextWeapon();

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponEquipSocketName = "WeaponPoint";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponArmorySocketName = "ArmorySocket";

  // Called when the game starts
  virtual void BeginPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
  UPROPERTY()
  ASTUBaseWeapon *CurrentWeapon = nullptr;

  UPROPERTY()
  TArray<ASTUBaseWeapon *> Weapons;

  int32 CurrentWeaponIndex = 0;

  void AttachWeaponSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
  void EquipWeapon(int32 WeaponIndex);
  void SpawnWeapons();
};
