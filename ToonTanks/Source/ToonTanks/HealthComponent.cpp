#include "HealthComponent.h"
#include "ToonTanks_GM.h"
#include <Kismet/GameplayStatics.h>

UHealthComponent::UHealthComponent(){
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay(){
	Super::BeginPlay();

	Health = MaxHealth;
	Alive = true;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGM = Cast<AToonTanks_GM>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser){
	if(Health <= 0.f && ToonTanksGM){
		Alive = false;
		ToonTanksGM->ActorDied(DamagedActor);
		return;
	}
	Health -= Damage;
};

