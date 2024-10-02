// Fill out your copyright notice in the Description page of Project Settings.


#include "Transporter.h"
#include "PressurePlate.h"
#include "CollectibleKey.h"

UTransporter::UTransporter()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	MoveTime = 3.0f;
	ActivatedTriggerCount = 0;

	bArePointsSet = false;
	bAllTriggerActorsTriggered = false;

	StartPoint = FVector::Zero();
	EndPoint = FVector::Zero();

}


void UTransporter::BeginPlay()
{
	Super::BeginPlay();

	if (bOwnerIsTriggerActor)
	{
		TriggerActors.Add(GetOwner());
	}

	for (AActor* TA : TriggerActors)
	{
		APressurePlate* PressurePlateActor = Cast<APressurePlate>(TA);
		if (PressurePlateActor)
		{
			PressurePlateActor->OnActivated.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
			PressurePlateActor->OnDeactivated.AddDynamic(this, &UTransporter::OnTriggerActorDeactivated);
			continue;
		}

		ACollectibleKey* KeyActor = Cast<ACollectibleKey>(TA);
		if (KeyActor)
		{
			KeyActor->OnCollected.AddDynamic(this, &UTransporter::OnTriggerActorActivated);
		}
	}
	
	
}


void UTransporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerActors.Num() > 0)
	{
		bAllTriggerActorsTriggered = (ActivatedTriggerCount >= TriggerActors.Num());
	}

	AActor* MyOwner = GetOwner();

	// Since this involves movement, we have to check
	// That we are only making these calls on the server
	if (MyOwner && MyOwner->HasAuthority() && bArePointsSet)
	{
		FVector CurrentLocation = MyOwner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;

		// Ternary reminder:
		// BoolToCheck ? if true : if false;
		FVector TargetLocation = bAllTriggerActorsTriggered ? EndPoint : StartPoint;

		// Move owning actor if not currently at target location
		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			MyOwner->SetActorLocation(NewLocation);
		}
	}

}

void UTransporter::SetPoints(FVector Point1, FVector Point2)
{
	if (Point1.Equals(Point2)) return;

	StartPoint = Point1;
	EndPoint = Point2;
	bArePointsSet = true;
}

void UTransporter::OnTriggerActorActivated()
{
	ActivatedTriggerCount++;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("ACTIVATED"));
}

void UTransporter::OnTriggerActorDeactivated()
{
	ActivatedTriggerCount--;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("DEACTIVATED"));
}

