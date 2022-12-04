// Shoot Them Up. All right reserved.

#include "UI/STUGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::BeginPlay()
{
  Super::BeginPlay();
  auto PlayerHudWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
  if (PlayerHudWidget) { PlayerHudWidget->AddToViewport(); }
}
void ASTUGameHUD::DrawHUD()
{
  Super::DrawHUD();
  // DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
  int32 SizeX = Canvas->SizeX;
  int32 SizeY = Canvas->SizeY;

  const TInterval<float> Center(SizeX * 0.5, SizeY * 0.5);

  const float        HalfLineSize  = 10.0f;
  const float        LineThickness = 2.0f;
  const FLinearColor Color         = FLinearColor::Green;

  DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, Color, LineThickness);
  DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, Color, LineThickness);
}
