#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::BeginPlay(){
	Super::BeginPlay();

    SetPlayerEnableState(false);
}

void AToonTanksPlayerController::SetPlayerEnableState(bool bEnableState){
    
    if(bEnableState){
        GetPawn()->EnableInput(this);
    }else{
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bEnableState;
}