#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanks_GM.generated.h"

UCLASS()
class TOONTANKS_API AToonTanks_GM : public AGameModeBase{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
};