// Shoot Them Up. All right reserved.

#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
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
