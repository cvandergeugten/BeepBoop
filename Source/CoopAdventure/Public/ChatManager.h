// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChatManager.generated.h"

/**
 * 
 */
UCLASS()
class COOPADVENTURE_API AChatManager : public AActor
{
	GENERATED_BODY()

public:
	AChatManager();

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> MessageLog;

	UFUNCTION(BlueprintCallable)
	void SendMessage(FString Message);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame if you want the actor to tick
	virtual void Tick(float DeltaTime) override;
	
};
