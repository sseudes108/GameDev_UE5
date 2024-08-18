#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot(){
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        UE_LOG(LogTemp, Error, TEXT("OwnerComp.GetAIOwner() == nullptr in %s"), *GetName());
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character == nullptr){
        UE_LOG(LogTemp, Error, TEXT("Character == nullptr in %s"), *GetName());
        return EBTNodeResult::Failed;
    }

    Character->Shoot();
    return EBTNodeResult::Succeeded;
}