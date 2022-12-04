// Shoot Them Up. All right reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjInit)
    : Super(
          ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
  SpringArmComponent->SetupAttachment(GetRootComponent());
  SpringArmComponent->bUsePawnControlRotation = true;
  SpringArmComponent->SocketOffset            = FVector(0.0f, 100.0f, 80.0f);
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  CameraComponent               = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
  CameraComponent->SetupAttachment(SpringArmComponent);

  HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("STUHealthComponent");

  HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
  HealthTextComponent->SetupAttachment(GetRootComponent());
  HealthTextComponent->SetOwnerNoSee(true);

  WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT(" STUWeaponComponent "));
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
  Super::BeginPlay();
  OnHealthChanged(HealthComponent->GetHealth());
  HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
  HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

  LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGrandLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
  PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
  PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
  PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRunning);
  PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRunning);
  PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
  PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
  PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
  PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}

bool ASTUBaseCharacter::IsRunning() const { return WantsToRun && IsMovingForward && !GetVelocity().IsZero(); }

float ASTUBaseCharacter::GetMovementDirection() const
{
  if (GetVelocity().IsZero()) return 0.0f;

  const auto VelocityNormal = GetVelocity().GetSafeNormal();
  const auto AngelBetween   = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
  const auto CrossProduct   = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

  return FMath::RadiansToDegrees(AngelBetween) * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
  IsMovingForward = Amount > 0.0;
  UE_LOG(LogTemp, Error, TEXT("Forward222: %f"), Amount);
  AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
  UE_LOG(LogTemp, Error, TEXT("Right: %f"), Amount);
  AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::LookUp(float Amount) { AddControllerPitchInput(Amount); }

void ASTUBaseCharacter::TurnAround(float Amount) { AddControllerYawInput(Amount); }

void ASTUBaseCharacter::StartRunning() { WantsToRun = true; }

void ASTUBaseCharacter::StopRunning() { WantsToRun = false; }

void ASTUBaseCharacter::OnDeath()
{
  UE_LOG(LogTemp, Error, TEXT("Player %s is Dead."), *GetName());

  PlayAnimMontage(DeathAnimMontage);

  GetCharacterMovement()->DisableMovement();

  SetLifeSpan(5.0f);

  if (Controller) { Controller->ChangeState(NAME_Spectating); }
  GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
  // WeaponComponent->StopFire();
}

void ASTUBaseCharacter::OnHealthChanged(float Health)
{
  HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUBaseCharacter::OnGrandLanded(const FHitResult &Hit)
{
  const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
  UE_LOG(LogTemp, Warning, TEXT("On Landed: %f"), FallVelocityZ);

  if (FallVelocityZ < LandedDamageVelocity.X) return;

  const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
  UE_LOG(LogTemp, Warning, TEXT("FinalDamage: %f"), FinalDamage);
  TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
