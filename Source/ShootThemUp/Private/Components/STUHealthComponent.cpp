// Shoot Them Up. All right reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
  PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
  Super::BeginPlay();

  check(MaxHealth > 0);

  AActor *ComponentOwner = GetOwner();
  if (ComponentOwner)
  {
    ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
  }

  SetHealth(MaxHealth);
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser
)
{
  if (Damage <= 0.0f || IsDead() && !GetWorld())
    return;

  SetHealth(Health - Damage);

  GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

  if (DamageType)
  {
    if (DamageType->IsA<USTUFireDamageType>())
    {
      UE_LOG(LogTemp, Error, TEXT("FireDamage: %f"), Damage);
    }
    else if (DamageType->IsA<USTUIceDamageType>())
    {
      UE_LOG(LogTemp, Error, TEXT("IceDamage: %f"), Damage);
    }
  }

  if (IsDead())
  {
    OnDeath.Broadcast();
  }
  else if (AutoHeal)
  {
    GetWorld()->GetTimerManager().SetTimer(
        HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay
    );
  }
}

void USTUHealthComponent::HealUpdate()
{
  SetHealth(Health + HealModifier);

  if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
  {
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
  }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
  Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
  OnHealthChanged.Broadcast(Health);
}
