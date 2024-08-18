#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;
class AShooterCharacter;

UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;
	UBlackboardComponent* BlackboardComponent;
};