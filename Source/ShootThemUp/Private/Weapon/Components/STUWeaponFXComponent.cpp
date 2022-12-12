// Shoot Them Up. All right reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent() { PrimaryComponentTick.bCanEverTick = false; }

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
  auto ImpactData = DefaultImpactData;
  UE_LOG(LogTemp, Warning, TEXT("PlayImpact Effect: %i"), Hit.PhysMaterial.IsValid());
  if (Hit.PhysMaterial.IsValid())
  {
    const auto PhysMat = Hit.PhysMaterial.Get();
    if (ImpactDataMap.Contains(PhysMat)) ImpactData = ImpactDataMap[PhysMat];
  }

  // Spawn NiagaraSystem
  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),               //
                                                 ImpactData.NiagaraEffect, //
                                                 Hit.ImpactPoint,          //
                                                 Hit.ImpactNormal.Rotation());
  // Spawn Decal Effect
  auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),                    //
                                                               ImpactData.DecalData.Material, //
                                                               ImpactData.DecalData.Size,     //
                                                               Hit.ImpactPoint,               //
                                                               Hit.ImpactNormal.Rotation(),   //
                                                               ImpactData.DecalData.LifeTime);

  if (DecalComponent) { DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime); }
}
  