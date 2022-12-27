// Shoot Them Up. All right reserved.

#include "AI/EQS/EnvQueryTest_PickUpCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

#include "Pickups/STUAmmoPickup.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickUpCouldBeTaken::UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer &ObjectInitializer) //
    : Super(ObjectInitializer)
{
  Cost          = EEnvTestCost ::High;
  ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
  SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickUpCouldBeTaken::RunTest(FEnvQueryInstance &QueryInstance) const
{
  for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
  {
    AActor    *ItemActor   = GetItemActor(QueryInstance, It.GetIndex());
    const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);

    const auto CouldBeTaken = PickupActor->CouldBeTaken();

    if (CouldBeTaken) { It.SetScore(TestPurpose, FilterType, true, true); }
    else It.ForceItemState(EEnvItemStatus::Failed);
  }
}
