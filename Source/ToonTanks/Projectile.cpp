#include "Projectile.h"

#include "Particles/ParticleSystemComponent.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>

AProjectile::AProjectile(){
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	MovementComponent->MaxSpeed = 1300.f;
	MovementComponent->InitialSpeed = 1300.f;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay(){
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound){
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr){
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor != nullptr && OtherActor != this && OtherActor != MyOwner){
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if(HitParticle){
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}

		if(HitSound){
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		if(HitCameraShakeClass){
			PlayerController->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	Destroy();
}