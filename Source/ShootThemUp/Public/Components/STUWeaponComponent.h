// Shoot Them Up. All right reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  USTUWeaponComponent();

  virtual void StartFire();
  virtual void NextWeapon();

  void StopFire();
  void Reload();
  void EquipWeapon(int32 WeaponIndex);

  bool GetWeaponUIData(FWeaponUIData &UIData) const;
  bool GetWeaponAmmoData(FAmmoData &AmmoData) const;
  bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);
  bool IsNeedAmmoForAnyWeapon(TSubclassOf<ASTUBaseWeapon> WeaponType);

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TArray<FWeaponData> WeaponData;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponEquipSocketName = "WeaponPoint";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponArmorySocketName = "ArmorySocket";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
  UAnimMontage *EquipAnimMontage;

  UPROPERTY()
  ASTUBaseWeapon *CurrentWeapon = nullptr;

  UPROPERTY()
  TArray<ASTUBaseWeapon *> Weapons;

  int32 CurrentWeaponIndex = 0;

  // Called when the game starts
  virtual void BeginPlay() override;
  // Called when the game end
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  bool CanFire() const;
  bool CanEquip() const;

private:
  UPROPERTY()
  UAnimMontage *CurrentReloadAnimMontage = nullptr;

  bool EquipAnimInProgress  = false;
  bool ReloadAnimInProgress = false;

  void AttachWeaponSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
  void SpawnWeapons();

  void PlayAnimMontage(UAnimMontage *AnimMontage);
  void InitAnimations();

  void OnEquipFinished(USkeletalMeshComponent *MeshComp);
  void OnReloadFinished(USkeletalMeshComponent *MeshComp);

  bool CanReload() const;

  void OnEmptyClip(ASTUBaseWeapon *AmmoEmptyWeapon);
  void ChangeClip();
};
