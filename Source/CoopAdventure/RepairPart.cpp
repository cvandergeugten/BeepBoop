// Fill out your copyright notice in the Description page of Project Settings.


#include "RepairPart.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARepairPart::ARepairPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootComp;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetupAttachment(RootComp);
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ARepairPart::OnOverlapBegin);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComp);
}

void ARepairPart::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Overlap event"));
}

// Called when the game starts or when spawned
void ARepairPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARepairPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

