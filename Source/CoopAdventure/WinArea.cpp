// Fill out your copyright notice in the Description page of Project Settings.


#include "WinArea.h"
#include "CoopAdventureCharacter.h"
#include "GameFramework/GameStateBase.h"

AWinArea::AWinArea()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	WinAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WinAreaBox"));
	SetRootComponent(WinAreaBox);

	bWinCondition = false;

	

}

void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
	if (AGameStateBase* GameState = GetWorld()->GetGameState<AGameStateBase>())
	{
		PlayerCount = GameState->PlayerArray.Num();
	}
}

void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{

		// Get the number of players
		if (CollectedParts == NumPartsToWin)
		{
			if (AGameStateBase* GameState = GetWorld()->GetGameState<AGameStateBase>())
			{
				PlayerCount = GameState->PlayerArray.Num();
				//UE_LOG(LogTemp, Log, TEXT("Number of players: %d"), PlayerCount);
			}


			if (!bWinCondition)
			{

				TArray<AActor*> OverlapActors;
				WinAreaBox->GetOverlappingActors(OverlapActors, ACoopAdventureCharacter::StaticClass());

				bWinCondition = OverlapActors.Num() == PlayerCount;
				if (bWinCondition)
				{
					UE_LOG(LogTemp, Warning, TEXT("WIN"));

					MulticastRPCWin();
				}
			}

		}
		

		
	}

}

void AWinArea::IncrementCollectedParts()
{
	CollectedParts++;
}

void AWinArea::MulticastRPCWin_Implementation()
{
	OnWinCondition.Broadcast();
}

