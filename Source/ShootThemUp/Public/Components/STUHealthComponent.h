// Shoot Them Up. All right reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"

#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  USTUHealthComponent();

  void SetHealth(float NewHealth);

  float const GetHealth() { return Health; }
  float const GetMaxHealth() { return MaxHealth; }

  UFUNCTION(BlueprintCallable)
  bool IsDead() const { return FMath::IsNearlyZero(Health); }
  UFUNCTION(BlueprintCallable)
  float GetHealthPercent() const { return Health / MaxHealth; }

  FOnDeath         OnDeath;
  FOnHealthChanged OnHealthChanged;

  bool TryToAddHealth(float HealthAmount);
  bool IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); }

protected:
  // Called when the game starts
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
  float MaxHealth = 100.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal");
  bool AutoHeal = false;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"));
  float HealUpdateTime = 1.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"));
  float HealDelay = 3.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"));
  float HealModifier = 1.0f;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX");
  TSubclassOf<UCameraShakeBase> CameraShake;

  virtual void BeginPlay() override;

private:
  float Health = 0.0f;

  FTimerHandle HealTimerHandle;

  UFUNCTION()
  void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                       class AController *InstigatedBy, AActor *DamageCauser);

  void HealUpdate();
  void PlayCameraShake();
};
