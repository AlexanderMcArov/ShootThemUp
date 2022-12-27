// Shoot Them Up. All right reserved.

#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BrainComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer &ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>(TEXT(" STUWeaponComponent ")))
{

  AutoPossessAI     = EAutoPossessAI::PlacedInWorld;
  AIControllerClass = ASTUAIController::StaticClass();

  bUseControllerRotationYaw = false;
  if (GetCharacterMovement())
  {
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->RotationRate                  = FRotator(0.0f, 200.0f, 0.0f);
  }
}

void ASTUAICharacter::OnDeath()
{
  const auto STUController = Cast<AAIController>(Controller);

  if (STUController && STUController->BrainComponent) { STUController->BrainComponent->Cleanup(); }
  Super::OnDeath();
}
