// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatManager.h"

AChatManager::AChatManager()
{

}

void AChatManager::SendMessage(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Send Message"));
}

void AChatManager::BeginPlay()
{

}

void AChatManager::Tick(float DeltaTime)
{

}
