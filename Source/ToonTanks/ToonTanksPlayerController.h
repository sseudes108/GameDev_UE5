#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	void SetPlayerEnableState(bool bEnableState);
};