// Shoot Them Up. All right reserved.

#include "Components/STUWeaponComponent.h"

#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
//
#include "Animations/AnimUtils.h"
#include "Animations/STUEquipAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USTUWeaponComponent::USTUWeaponComponent() { PrimaryComponentTick.bCanEverTick = false; }

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
  Super::BeginPlay();
  InitAnimations();
  CurrentWeaponIndex = 0;
  SpawnWeapons();
  EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  CurrentWeapon = nullptr;
  for (auto Weapon : Weapons)
  {
    Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    Weapon->Destroy();
  }

  Weapons.Empty();
  Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  if (!Character || !GetWorld()) return;

  for (auto OneWeaponData : WeaponData)
  {
    auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
    if (!Weapon) continue;

    Weapon->OnClimpEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
    Weapon->SetOwner(Character);
    Weapons.Add(Weapon);

    AttachWeaponSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
  }
}

void USTUWeaponComponent::AttachWeaponSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent,
                                             const FName &SocketName)
{
  if (!Weapon || !SceneComponent) return;

  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
  Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
  if (Weapons.Num() <= WeaponIndex || WeaponIndex < 0 || Weapons.Num() == 0) return;
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  if (!Character) return;

  if (CurrentWeapon)
  {
    CurrentWeapon->StopFire();
    AttachWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
  }

  CurrentWeapon            = Weapons[WeaponIndex];
  CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
  EquipAnimInProgress      = true;

  AttachWeaponSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

  PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage *AnimMontage)
{
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  if (!Character) return;

  Character->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::Reload() { ChangeClip(); }

void USTUWeaponComponent::StartFire()
{
  if (!CanFire()) return;

  CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
  if (!CurrentWeapon) return;

  CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon()
{
  if (!CanEquip()) return;

  UE_LOG(LogTemp, Warning, TEXT("NExtWeapon"));
  CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
  EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::InitAnimations()
{
  auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipAnimNotify>(EquipAnimMontage);
  if (EquipFinishedNotify) { EquipFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnEquipFinished); }
  else
  {
    UE_LOG(LogWeaponComponent, Warning, TEXT("Not set Equip Notify."));
    checkNoEntry();
  }

  for (auto OneWeapon : WeaponData)
  {
    auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(OneWeapon.ReloadAnimMontage);
    if (!ReloadFinishedNotify)
    {
      UE_LOG(LogWeaponComponent, Warning, TEXT("Not set Equip Notify."));
      checkNoEntry();
    }

    ReloadFinishedNotify->OnNotify.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
  }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent *MeshComp)
{
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  if (!Character || Character->GetMesh() != MeshComp) return;

  EquipAnimInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComp)
{
  ACharacter *Character = Cast<ACharacter>(GetOwner());
  if (!Character || Character->GetMesh() != MeshComp) return;
  
  CurrentWeapon->ChangeClip();
  ReloadAnimInProgress = false;
}

void USTUWeaponComponent::OnEmptyClip() { ChangeClip(); }
void USTUWeaponComponent::ChangeClip()
{
  if (!CanReload()) return;

  ReloadAnimInProgress = true;
  CurrentWeapon->StopFire();
  PlayAnimMontage(CurrentReloadAnimMontage);
}

//

bool USTUWeaponComponent::CanFire() const { return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress; }

bool USTUWeaponComponent::CanReload() const
{
  return CurrentWeapon            //
         && !EquipAnimInProgress  //
         && !ReloadAnimInProgress //
         && CurrentWeapon->CanReload();
}

bool USTUWeaponComponent::CanEquip() const { return !EquipAnimInProgress && !ReloadAnimInProgress; }

bool USTUWeaponComponent::GetWeaponUIData(FWeaponUIData &UIData) const
{
  if (CurrentWeapon)
  {
    UIData = CurrentWeapon->GetUIData();
    return true;
  }
  return false;
}

bool USTUWeaponComponent::GetWeaponAmmoData(FAmmoData &AmmoData) const
{
  if (CurrentWeapon)
  {
    AmmoData = CurrentWeapon->GetAmmoData();
    return true;
  }
  return false;
}
