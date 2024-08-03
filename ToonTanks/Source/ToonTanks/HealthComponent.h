#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent{
	GENERATED_BODY()

public:	
	UHealthComponent();

	bool IsAlive() {return Alive; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(VisibleAnywhere)
	bool Alive;

	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

	class AToonTanks_GM* ToonTanksGM;
};