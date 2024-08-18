#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include <Kismet/GameplayStatics.h>

AGun::AGun(){
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(Root);
}

void AGun::BeginPlay(){
	Super::BeginPlay();
}
	
void AGun::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger(){
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMeshComponent, TEXT("MuzzleFlashSocket"));

	if(OwnerController == nullptr) { return; }

	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);

	FHitResult HitResult;
	FVector End = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(bHit){
		AActor* DamagedActor = HitResult.GetActor();
		FVector ShotDirection = -OwnerRotation.Vector();

		if(DamagedActor != nullptr){
			// if(DamagedActor == Owner) { return; }
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			DamagedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletImpact, HitResult.ImpactPoint, ShotDirection.Rotation());
	}
}

void AGun::Initialize(AController* Controller){
	OwnerController = Controller;
}