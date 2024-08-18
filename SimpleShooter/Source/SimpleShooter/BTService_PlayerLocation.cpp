#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>

UBTService_PlayerLocation::UBTService_PlayerLocation(){
    NodeName = TEXT("Update Last Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(PlayerPawn == nullptr){
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    }

    if(BlackboardComponent == nullptr){
        BlackboardComponent = OwnerComp.GetBlackboardComponent();
    }

    BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}