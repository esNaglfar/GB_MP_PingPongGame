// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PingPongGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/PingPongPlayerPawn.h"
#include "PlayerControllers/PingPongPlayerController.h"

APingPongGameModeBase::APingPongGameModeBase()
{

	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UWorld* world = GetWorld();

	if(world && (!PlayerOneStart && !PlayerTwoStart))
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(world, APlayerStart::StaticClass(), PlayerStarts);

		if(PlayerStarts.Num() > 0) PlayerOneStart = (APlayerStart*) PlayerStarts[0];
		if(PlayerStarts.Num() > 1) PlayerTwoStart = (APlayerStart*) PlayerStarts[1];

		APingPongPlayerController* CurrentPlayer = NULL;
		APlayerStart* startPos = NULL;

		if(PlayerOne == NULL)
		{
			PlayerOne = (APingPongPlayerController*) NewPlayer;
			CurrentPlayer = PlayerOne;
			startPos = PlayerOneStart;
			UE_LOG(LogTemp, Warning, TEXT("GameMode: Init player one"));
		}
		else if(PlayerTwo == NULL)
		{
			PlayerTwo = (APingPongPlayerController*) NewPlayer;
			CurrentPlayer = PlayerTwo;
			startPos = PlayerTwoStart;
			UE_LOG(LogTemp, Warning, TEXT("GameMode: Init player two"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("It is already two players here. Find another match..."));
			return;
		}

		APingPongPlayerPawn* newPawn = Cast<APingPongPlayerPawn>(NewPlayer->GetPawn());

		if(!newPawn)
		{
			newPawn = world->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
		}

		if(startPos && newPawn)
		{
			newPawn->SetActorLocation(startPos->GetActorLocation());
			newPawn->SetActorRotation(startPos->GetActorRotation());
			NewPlayer->SetPawn(newPawn);

			CurrentPlayer->SetStartTransform(startPos->GetActorTransform());
			CurrentPlayer->Initialize();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No start position setted in GameMode"));
		}
	}
	
}
