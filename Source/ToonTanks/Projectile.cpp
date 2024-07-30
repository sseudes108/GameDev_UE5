#include "Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>

AProjectile::AProjectile(){
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	MovementComponent->MaxSpeed = 1300.f;
	MovementComponent->InitialSpeed = 1300.f;
}

void AProjectile::BeginPlay(){
	Super::BeginPlay();
}