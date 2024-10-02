// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleKey.h"
#include "Net/UnrealNetwork.h"
#include "CoopAdventureCharacter.h"

// Sets default values
ACollectibleKey::ACollectibleKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	RotationSpeed = 100.0f;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComp);
	Capsule->SetIsReplicated(true);
	Capsule->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Capsule->SetCapsuleHalfHeight(150.0f);
	Capsule->SetCapsuleRadius(100.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	CollectAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Collect Audio"));
	CollectAudio->SetupAttachment(RootComp);
	CollectAudio->SetAutoActivate(false);

}

void ACollectibleKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//
	DOREPLIFETIME(ACollectibleKey, bIsCollected);

}

// Called when the game starts or when spawned
void ACollectibleKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectibleKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		// Rotate key mesh
		Mesh->AddRelativeRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));

		// Check to see if there are any actors colliding with the capsule mesh
		TArray<AActor*> OverlappingActors;
		Capsule->GetOverlappingActors(OverlappingActors, ACoopAdventureCharacter::StaticClass());
		
		// Capsule overlapping with player character
		if (!OverlappingActors.IsEmpty())
		{
			if (!bIsCollected)
			{
				bIsCollected = true;
				// Call for the server for bIsCollected
				OnRep_IsCollected();
			}
		}
	}

}

void ACollectibleKey::OnRep_IsCollected()
{
	if (HasAuthority())
	{
		if (bIsCollected)
		{
			OnCollected.Broadcast();
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("OnRep_IsCollected called from the server"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("OnRep_IsCollected called from the client"));
	}

	Mesh->SetVisibility(!bIsCollected);

	CollectAudio->Play();

	if (bIsCollected)
	{
		if (KeyHolderRef)
		{
			KeyHolderRef->ActivateKeyMesh();
		}
	}
}

