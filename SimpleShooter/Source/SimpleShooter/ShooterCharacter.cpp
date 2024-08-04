#include "ShooterCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AShooterCharacter::AShooterCharacter(){
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay(){
	Super::BeginPlay();
}

void AShooterCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	auto vel = GetVelocity();
	auto velLenght = vel.Size();
	UE_LOG(LogTemp, Warning, TEXT("Velocity: %f"), velLenght);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	//Link inputmapping
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Bind Actions
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		//Move
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);

		//Look
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);

		//jump
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	}
}

void AShooterCharacter::Move(const FInputActionValue& Value){
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(Controller != nullptr){
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AShooterCharacter::Look(const FInputActionValue& Value){
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if(Controller != nullptr){
		AddControllerYawInput(RotationXSensitivity * GetWorld()->GetDeltaSeconds() * LookAxisVector.X);
		AddControllerPitchInput(RotationYSensitivity * GetWorld()->GetDeltaSeconds() * LookAxisVector.Y);
	}
}