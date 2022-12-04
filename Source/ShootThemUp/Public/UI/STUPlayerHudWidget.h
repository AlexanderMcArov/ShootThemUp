// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHudWidget.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHudWidget : public UUserWidget
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "UI")
  float GetHealthPercent() const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool GetWeaponUIData(FWeaponUIData &UIData) const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool GetWeaponAmmoData(FAmmoData &AmmoData) const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool IsPlayerAlive() const;

  UFUNCTION(BlueprintCallable, Category = "UI")
  bool IsPlayerSpectating() const;

private:

};
