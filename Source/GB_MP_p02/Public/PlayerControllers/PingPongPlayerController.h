// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

class APingPongPlatform;
/**
 * 
 */
UCLASS()
class GB_MP_P02_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTransform StartTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<APingPongPlatform> PlatformClass;

	UPROPERTY()
	APingPongPlatform* Platform;

public:
	APingPongPlayerController();

	UFUNCTION()
	void SetStartTransform(FTransform NewStartTransform);

	UFUNCTION(Server,Reliable, WithValidation)
	void Initialize();

	UFUNCTION(Server,Reliable,WithValidation)
	void SpawningPlatform(TSubclassOf<APingPongPlatform> SpawnClass);

	virtual void SetupInputComponent() override;

protected:

	void MoveRight(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float AxisValue);
	
};
