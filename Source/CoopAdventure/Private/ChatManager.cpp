// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatManager.h"
#include "CoopAdventure/BeepBoopPreCompiled.h"

AChatManager::AChatManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}



void AChatManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChatManager, MessageLog);
}

void AChatManager::OnRep_UpdateMessageLog()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "OnRep Function Called");
	OnMessageLogUpdated.Broadcast();
}

void AChatManager::UpdateMessageLog(const FString& Message)
{
	MessageLog.Add(Message);
	OnMessageLogUpdated.Broadcast();
}

void AChatManager::BeginPlay()
{

}

void AChatManager::Tick(float DeltaTime)
{

}
