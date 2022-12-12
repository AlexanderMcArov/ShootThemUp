// Shoot Them Up. All right reserved.

#include "Components/STUHealthComponent.h"
#include "Camera/CameraShake.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() { PrimaryComponentTick.bCanEverTick = false; }

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
  Super::BeginPlay();

  check(MaxHealth > 0);

  AActor *ComponentOwner = GetOwner();
  if (ComponentOwner) { ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage); }

  SetHealth(MaxHealth);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                          AController *InstigatedBy, AActor *DamageCauser)
{
  if (Damage <= 0.0f || IsDead() && !GetWorld()) return;

  SetHealth(Health - Damage);

  GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

  if (DamageType)
  {
    if (DamageType->IsA<USTUFireDamageType>()) { UE_LOG(LogTemp, Error, TEXT("FireDamage: %f"), Damage); }
    else if (DamageType->IsA<USTUIceDamageType>()) { UE_LOG(LogTemp, Error, TEXT("IceDamage: %f"), Damage); }
  }

  if (IsDead()) { OnDeath.Broadcast(); }
  else if (AutoHeal)
  {
    GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime,
                                           true, HealDelay);
  }

  PlayCameraShake();
}

void USTUHealthComponent::HealUpdate()
{
  SetHealth(Health + HealModifier);

  if (IsHealthFull() && GetWorld()) { GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle); }
}

void USTUHealthComponent::PlayCameraShake()
{
  if (IsDead()) return;

  const auto Player = Cast<APawn>(GetOwner());
  if (!Player) return;

  const auto Controller = Player->GetController<APlayerController>();
  if (!Controller || !Controller->PlayerCameraManager) return;

  Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
  const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
  const auto HealthDealta = NextHealth - Health;

  Health = NextHealth;
  OnHealthChanged.Broadcast(Health, HealthDealta);
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
  if (IsDead()) return false;
  if (IsHealthFull()) return false;
  SetHealth(Health + HealthAmount);
  return true;
}
