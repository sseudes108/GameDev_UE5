// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/CapsuleComponent.h>
#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector lookAtTarget){
	FVector ToTarget = lookAtTarget - TurretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(lookAtRotation);
}

void ABasePawn::Fire(){
	FVector FirePoint = ProjectileSpawnPoint->GetComponentLocation();
	DrawDebugSphere(
		GetWorld(),
		FirePoint,
		25.f,
		10,
		FColor::Yellow,
		false,
		3.f
	);
}