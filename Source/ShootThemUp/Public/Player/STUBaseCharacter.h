// Shoot Them Up. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;

UCLASS()

class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ASTUBaseCharacter(const FObjectInitializer &ObjInit);

protected:
  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  USTUHealthComponent *HealthComponent;

  UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
  UTextRenderComponent *HealthTextComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
  USTUWeaponComponent *WeaponComponent;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
  UAnimMontage *DeathAnimMontage;

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
  FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
  FVector2D LandedDamage = FVector2D(1.0f, 100.0f);

  
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  bool IsRunning() const;

  UFUNCTION(BlueprintCallable, Category = "Movement")
  float GetMovementDirection() const;

private:
  bool WantsToRun = false;
  bool IsMovingForward = false;

  void MoveForward(float Amount);
  void MoveRight(float Amount);

  void LookUp(float Amount);
  void TurnAround(float Amount);

  void StartRunning();
  void StopRunning();

  void OnDeath();
  void OnHealthChanged(float);

  UFUNCTION()
  void OnGrandLanded(const FHitResult &Hit);

};
