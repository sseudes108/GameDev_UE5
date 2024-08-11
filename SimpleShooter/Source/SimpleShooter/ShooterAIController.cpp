#include "ShooterAIController.h"
#include <Kismet/GameplayStatics.h>

void AShooterAIController::BeginPlay(){
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AShooterAIController::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);

    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);
        UE_LOG(LogTemp, Warning, TEXT("Your message"));
    }else{
        UE_LOG(LogTemp, Warning, TEXT("AIBehavior == nullptr"));
    }

    // if(LineOfSightTo(PlayerPawn)){
    //     SetFocus(PlayerPawn);
    //     MoveToActor(PlayerPawn, AcceptanceRadius);

    //     if(NeedReset) { return; }
    //     NeedReset = true;
    // }else{
    //     if(!NeedReset) { return; }

    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    //     NeedReset = false;
    // }
}