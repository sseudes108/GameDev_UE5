#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay(){
    Super::BeginPlay();

    AICharacter = Cast<AShooterCharacter>(GetPawn());

    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);

        Blackboard = GetBlackboardComponent();
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if(Blackboard != nullptr){
            Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        }
    }
}

void AShooterAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);

    if(AICharacter != nullptr){
        if(AICharacter->IsDead()){
            return;
        }
    }

    if(PlayerPawn != nullptr){

        if(LineOfSightTo(PlayerPawn)){
            if(Blackboard != nullptr){
                GetPlayerLocation();
            }else{
                Blackboard = GetBlackboardComponent();
                GetPlayerLocation();
            }
        }else{
            if(Blackboard != nullptr){
                ClearPlayerLocation();
            }else{
                Blackboard = GetBlackboardComponent();
                ClearPlayerLocation();
            }
        }
        
    }else{
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    }
}

void AShooterAIController::GetPlayerLocation(){
    Blackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    Blackboard->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
}

void AShooterAIController::ClearPlayerLocation(){
    Blackboard->ClearValue(TEXT("PlayerLocation"));
}