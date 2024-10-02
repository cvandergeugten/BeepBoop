// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WinArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinAreaOnWinCondition);

UCLASS()
class COOPADVENTURE_API AWinArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AWinArea();

protected:
	virtual void BeginPlay() override;

	int32 PlayerCount;

	UPROPERTY(EditAnywhere, Category = "Game")
	int32 CollectedParts;

	UPROPERTY(EditAnywhere, Category = "Game")
	int32 NumPartsToWin;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* WinAreaBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bWinCondition;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCWin();

	UPROPERTY(BlueprintAssignable)
	FWinAreaOnWinCondition OnWinCondition;

	UFUNCTION(BlueprintCallable)
	void IncrementCollectedParts();



};
