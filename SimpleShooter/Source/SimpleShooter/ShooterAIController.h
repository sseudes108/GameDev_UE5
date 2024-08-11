#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	bool NeedReset = false;
	APawn* PlayerPawn;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UBlackboardComponent* BlackboardComponent;
};