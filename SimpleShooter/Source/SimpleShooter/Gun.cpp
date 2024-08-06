#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
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

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) { return; }

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) { return; }

	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);

	FHitResult HitResult;
	FVector End = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

	if(bHit){
		DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 15, FColor::Yellow, true);
	}
}