// Shoot Them Up. All right reserved.

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHud.h"

ASTUGameModeBase::ASTUGameModeBase()
{
  DefaultPawnClass = ASTUBaseCharacter::StaticClass();
  PlayerControllerClass = ASTUPlayerController::StaticClass();
  HUDClass = ASTUGameHUD::StaticClass();
}