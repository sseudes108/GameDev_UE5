#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include "HealthComponent.h"

void ATower::BeginPlay(){
	Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TankHealth = Tank->GetComponentByClass<UHealthComponent>();

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);

    if(IsInFireRange()){
        RotateTurret(TankLocation);
    }
}

void ATower::HandleDesctruction(){
    Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition(){
    if(IsInFireRange() && TankHealth->IsAlive()){
        Fire();
    }
}

bool ATower::IsInFireRange(){
    if(Tank){
        TankLocation = Tank->GetActorLocation();
        float Distance = FVector::Dist(GetActorLocation(), TankLocation);
        return Distance < FireRange;
    }
    
    return false;
}