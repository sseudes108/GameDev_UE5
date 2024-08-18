#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay(){
    Super::BeginPlay();

    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);

        Blackboard = GetBlackboardComponent();
        if(Blackboard != nullptr){
            Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        }
    }
}
