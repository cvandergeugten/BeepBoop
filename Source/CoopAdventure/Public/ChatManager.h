// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ChatManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMessageLogUpdated);

UCLASS()
class COOPADVENTURE_API AChatManager : public AActor
{
	GENERATED_BODY()

public:
	AChatManager();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_UpdateMessageLog, BlueprintReadWrite)
	TArray<FString> MessageLog;

	UFUNCTION()
	void OnRep_UpdateMessageLog();

	UFUNCTION()
	void UpdateMessageLog(const FString& Message);

	UPROPERTY(BlueprintAssignable, Category = "Chat")
	FOnMessageLogUpdated OnMessageLogUpdated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame if you want the actor to tick
	virtual void Tick(float DeltaTime) override;
	
};
