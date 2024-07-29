// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>

ATank::ATank(){
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay(){
	Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

    if(PlayerController){
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false,
            HitResult
        );

        DrawDebugSphere(
            GetWorld(),
            HitResult.ImpactPoint,
            25.f,
            10,
            FColor::Red,
            false
        );

        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value){
    FVector DeltaLocation(0.f);
    DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * MoveSpeed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value){
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed;
    AddActorLocalRotation(DeltaRotation, true);
}