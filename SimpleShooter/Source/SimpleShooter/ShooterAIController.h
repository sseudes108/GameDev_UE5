#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class AShooterCharacter;

UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	bool NeedReset = false;
	APawn* PlayerPawn;
	AShooterCharacter* AICharacter;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UBlackboardComponent* BlackboardComponent;

	void GetPlayerLocation();
	void ClearPlayerLocation();
};