#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor{
	GENERATED_BODY()

public:	
	AGun();

	void PullTrigger();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcess = "true"));
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAcess = "true"));
	USkeletalMeshComponent* SkeletalMeshComponent;
};
