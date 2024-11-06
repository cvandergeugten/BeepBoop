#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"



static AActor* PerformRaycastFromMouse(UWorld* World, APlayerController* PlayerController) {
	if (!World || !PlayerController) 
	{
		return nullptr;
	}
	FVector WorldLocation, WorldDirection;
	if (!PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to deproject mouse position"));
		return nullptr;
	}
	FVector Start = WorldLocation;
	FVector End = Start + (WorldDirection * 10000.0f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("TraceTag")), true);
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(PlayerController->GetPawn());

	bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		TraceParams
	);

	DrawDebugLine(World, Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

	if (bHit)
	{
		// Check if the hit actor is of type ACustomObject
		if (HitResult.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit an object of class AActor at location: %s"), *HitResult.ImpactPoint.ToString());
			return HitResult.GetActor();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit an object, but it is not of class AActor"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No object was hit"));
	}

	return nullptr;
}