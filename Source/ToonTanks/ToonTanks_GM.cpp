#include "ToonTanks_GM.h"

#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

#include <Kismet/GameplayStatics.h>

void AToonTanks_GM::BeginPlay(){
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

void AToonTanks_GM::ActorDied(AActor* DeadActor){
    if(DeadActor == Tank){
        Tank->HandleDestruction();
        if(ToonTanksPlayerController){
            ToonTanksPlayerController->SetPlayerEnableState(false);
            return;
        }
    }

    if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){
        DestroyedTower->HandleDesctruction();
        return;
    }
}