#pragma once
#include "STUCoreTypes.generated.h"

class ASTUBaseWeapon;

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClimpEmptySignature, ASTUBaseWeapon *);

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

// VFX

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecaLData {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UMaterialInterface *Material;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  FVector Size = FVector(10.0f);

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  float LifeTime = 5.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  UNiagaraSystem *NiagaraEffect;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
  FDecaLData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData {
  GENERATED_USTRUCT_BODY()
  // Max Players
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
  int32 PlayersNum = 5;

  // Max Rounds
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "10"))
  int32 RoundsNum = 5;

  // Time in seconds for one round
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "5", ClampMax = "300"))
  int32 RoundTime = 10;
};