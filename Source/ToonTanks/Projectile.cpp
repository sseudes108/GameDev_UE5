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

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	UE_LOG(LogTemp, Warning, TEXT("HitComp - %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherActor - %s"), *OtherActor->GetActorNameOrLabel());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp - %s"), *OtherComp->GetName());
}