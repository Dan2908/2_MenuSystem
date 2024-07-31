// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetActorTransform().TransformPosition(TargetLocation);
	GlobalDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		Move(DeltaTime);
	}

}

void AMovingPlatform::Move(float DeltaTime)
{
	if (ActiveTriggers == 0)
	{
		return;
	}

	const FVector Location = GetActorLocation() + GlobalDirection * PlatformSpeed * DeltaTime;

	const FVector NewDirection = (GlobalTargetLocation - Location).GetSafeNormal();
	if (!FVector::Coincident(GlobalDirection, NewDirection)) // Current location has passed the target location. (opposite directios)
	{
		SwitchTargetLocation();
	}

	SetActorLocation(Location);

}

void AMovingPlatform::SwitchTargetLocation()
{
	const FVector Aux = GlobalStartLocation;

	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Aux;
	GlobalDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
}
