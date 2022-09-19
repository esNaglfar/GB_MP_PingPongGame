// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PingPongPlatform.generated.h"

UCLASS()
class GB_MP_P02_API APingPongPlatform : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Parameters")
	float MoveSpeed = 500.f;

		
public:	
	// Sets default values for this actor's properties
	APingPongPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveRight(float AxisValue);
	
};
