#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"

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