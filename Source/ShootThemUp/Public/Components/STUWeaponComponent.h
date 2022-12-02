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

  void StartFire();
  void StopFire();
  void NextWeapon();
  void Reload();

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TArray<FWeaponData> WeaponData;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponEquipSocketName = "WeaponPoint";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  FName WeaponArmorySocketName = "ArmorySocket";

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
  UAnimMontage *EquipAnimMontage;

  // Called when the game starts
  virtual void BeginPlay() override;
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
  UPROPERTY()
  ASTUBaseWeapon *CurrentWeapon = nullptr;

  UPROPERTY()
  TArray<ASTUBaseWeapon *> Weapons;

  UPROPERTY()
  UAnimMontage *CurrentReloadAnimMontage = nullptr;

  int32 CurrentWeaponIndex = 0;
  bool EquipAnimInProgress = false;
  bool ReloadAnimInProgress = false;

  void AttachWeaponSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
  void EquipWeapon(int32 WeaponIndex);
  void SpawnWeapons();

  void PlayAnimMontage(UAnimMontage *AnimMontage);
  void InitAnimations();

  void OnEquipFinished(USkeletalMeshComponent *MeshComp);
  void OnReloadFinished(USkeletalMeshComponent *MeshComp);

  bool CanFire() const;
  bool CanEquip() const;
  bool CanReload() const;

  void OnEmptyClip();
  void ChangeClip();
};
