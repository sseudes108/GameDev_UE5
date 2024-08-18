#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen(){
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(PlayerPawn == nullptr){
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    }

    if(BlackboardComponent == nullptr){
        BlackboardComponent = OwnerComp.GetBlackboardComponent();
    }

    if(AIController == nullptr){
        AIController = OwnerComp.GetAIOwner();
    }

    if(AIController->LineOfSightTo(PlayerPawn)){
        BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }else{
        BlackboardComponent->ClearValue(GetSelectedBlackboardKey());
    }
}