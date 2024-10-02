// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleKeyHolder.h"

// Sets default values
ACollectibleKeyHolder::ACollectibleKeyHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	KeyMeshRotationSpeed = 100.0f;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(RootComp);
	KeyMesh->SetIsReplicated(true);
	KeyMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));

}

// Called when the game starts or when spawned
void ACollectibleKeyHolder::BeginPlay()
{
	Super::BeginPlay();

	KeyMesh->SetVisibility(false);
	
}

// Called every frame
void ACollectibleKeyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		KeyMesh->AddRelativeRotation(FRotator(0.0f, KeyMeshRotationSpeed * DeltaTime, 0.0f));
	}

}

void ACollectibleKeyHolder::ActivateKeyMesh()
{
	KeyMesh->SetVisibility(true);
}

