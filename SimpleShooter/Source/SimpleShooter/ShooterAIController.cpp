#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay(){
    Super::BeginPlay();

    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);

        Blackboard = GetBlackboardComponent();
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);

    if(LineOfSightTo(PlayerPawn)){
        Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        Blackboard->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }else{
        Blackboard->ClearValue(TEXT("PlayerLocation"));
    }
}