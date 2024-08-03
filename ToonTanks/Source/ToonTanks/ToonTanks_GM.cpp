#include "ToonTanks_GM.h"

#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

#include <Kismet/GameplayStatics.h>

void AToonTanks_GM::BeginPlay(){
    Super::BeginPlay();

    HandleGameStart();
    TargetTowers = GetTargetTowerCount();
}

void AToonTanks_GM::ActorDied(AActor* DeadActor){
    if(DeadActor == Tank){
        Tank->HandleDestruction();
        
        if(ToonTanksPlayerController){
            ToonTanksPlayerController->SetPlayerEnableState(false);
            GameOver(false);
            return;
        }
    }

    if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDesctruction();

        TargetTowers--;
        if(TargetTowers == 0) {
            GameOver(true);
        }

        return;
    }
}

void AToonTanks_GM::HandleGameStart(){
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    FTimerHandle PlayerEnableTimerHandler;
    FTimerDelegate PlayerTimerDelegate = FTimerDelegate::CreateUObject(
        ToonTanksPlayerController, 
        &AToonTanksPlayerController::SetPlayerEnableState, 
        true
    );

    GetWorldTimerManager().SetTimer(
        PlayerEnableTimerHandler,
        PlayerTimerDelegate,
        StartDelay,
        false
    );
}

int32 AToonTanks_GM::GetTargetTowerCount(){
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}