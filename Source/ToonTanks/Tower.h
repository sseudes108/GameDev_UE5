#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDesctruction();

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;
	class UHealthComponent* TankHealth;

	FVector TankLocation;
	bool IsInFireRange();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 1200.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.5f;
	void CheckFireCondition();
};
