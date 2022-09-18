// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/PingPongPlayerController.h"
#include "Actors/PingPongPlatform.h"


APingPongPlayerController::APingPongPlayerController()
{
	SetReplicates(true);
}

void APingPongPlayerController::SetStartTransform(FTransform NewStartTransform)
{
	StartTransform = NewStartTransform;	
}

void APingPongPlayerController::Initialize_Implementation()
{
	Platform = (APingPongPlatform*) GetWorld()->SpawnActor<APingPongPlatform>(PlatformClass);
	if(Platform)
	{
		Platform->SetActorLocation(StartTransform.GetLocation());
		Platform->SetActorRotation(StartTransform.GetRotation());
	}
}

bool APingPongPlayerController::Initialize_Validate()
{
	return true;
}

void APingPongPlayerController::SpawningPlatform_Implementation(TSubclassOf<APingPongPlatform> SpawnClass)
{
	if(Platform) Platform->Destroy();

	SpawningPlatform(PlatformClass);
}

bool APingPongPlayerController::SpawningPlatform_Validate(TSubclassOf<APingPongPlatform> SpawnClass)
{
	return PlatformClass != NULL;
}

void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move", this, &APingPongPlayerController::MoveRight);
}

void APingPongPlayerController::MoveRight(float AxisValue)
{
	if(AxisValue != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController : Moving platform"));
		Server_MoveRight(AxisValue);
	}
}

void APingPongPlayerController::Server_MoveRight_Implementation(float AxisValue)
{
	if(Platform)
	{
		if(AxisValue != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Server: MovingPlatform"));
			Platform->Server_MoveRight(AxisValue);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController: No platform here"));
	}
}

bool APingPongPlayerController::Server_MoveRight_Validate(float AxisValue)
{
	return AxisValue >= -1 && AxisValue <= 1 ? true : false;
}
