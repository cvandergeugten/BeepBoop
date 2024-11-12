// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatManager.h"

AChatManager::AChatManager()
{

}

void AChatManager::SendMessage(FString Message)
{
	MessageLog.Add(Message);
}

void AChatManager::BeginPlay()
{

}

void AChatManager::Tick(float DeltaTime)
{

}
