// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PingPongPlatform.h"

// Sets default values
APingPongPlatform::APingPongPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(BoxCollision);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	BodyMesh->SetupAttachment(BoxCollision);
	BodyMesh->SetIsReplicated(true);
	
	SetReplicates(true);
	SetReplicateMovement(true);

}

// Called when the game starts or when spawned
void APingPongPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APingPongPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APingPongPlatform::Server_MoveRight_Implementation(float AxisValue)
{
	FVector currLocation = GetActorLocation();
	FVector nextLocation = currLocation + GetActorRightVector() * MoveSpeed * AxisValue * GetWorld()->DeltaTimeSeconds;
	if(!SetActorLocation(nextLocation, true))
	{
		SetActorLocation(currLocation);
	}
}

bool APingPongPlatform::Server_MoveRight_Validate(float AxisValue)
{
	return AxisValue >= -1 && AxisValue <= 1 ? true : false;
}

