#pragma once
#include "STUCoreTypes.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
DECLARE_MULTICAST_DELEGATE(FOnClimpEmptySignature);

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FAmmoData {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  int32 Bullets;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
  int32 Clips;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TSubclassOf<ASTUBaseWeapon> WeaponClass;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  UAnimMontage *ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponUI")
  UTexture2D *MainIcon;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponUI")
  UTexture2D *CrossHairIcon;
  
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WeaponUI")
  float GoGo = 0.1f;
};
