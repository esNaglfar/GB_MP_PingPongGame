// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "PingPongGameModeBase.generated.h"

class APingPongPlayerController;
/**
 * 
 */
UCLASS()
class GB_MP_P02_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	APingPongPlayerController* PlayerOne = NULL;
	
	UPROPERTY()
	APingPongPlayerController* PlayerTwo = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerStart* PlayerOneStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerStart* PlayerTwoStart;


public:

	APingPongGameModeBase();

	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
