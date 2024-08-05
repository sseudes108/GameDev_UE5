#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintreadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TSubclassOf<AGun> GunClass;

public:
	AShooterCharacter();

protected:
	virtual void BeginPlay() override;

private:
	//Methods

	//Inputs
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Shoot();

	//Gun
	void SetUpGun();

private:
	//Variables
	UPROPERTY(EditAnywhere, Category = Input)
	float RotationXSensitivity = 50.f;

	UPROPERTY(EditAnywhere, Category = Input)
	float RotationYSensitivity = 40.f;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	AGun* Gun;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};