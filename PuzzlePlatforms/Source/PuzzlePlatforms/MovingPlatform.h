// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float PlatformSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Platform", Meta = (MakeEditWidget))
	FVector TargetLocation;

	inline void AddActiveTriggers() { ++ActiveTriggers; }
	inline void RemoveActiveTriggers() { --ActiveTriggers; }

protected:

	void Move(float DeltaTime);

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

private:

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	FVector GlobalDirection;

	void SwitchTargetLocation();
};
