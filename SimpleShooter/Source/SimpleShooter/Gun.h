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
	
	void Initialize(AController* OwnerController);
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

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* BulletImpact;

	AController* OwnerController;
	FVector OwnerLocation;
	FRotator OwnerRotation;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;
};