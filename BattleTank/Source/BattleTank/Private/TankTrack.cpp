// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "SprungWheel.h"
#include "SuspensionSpawnPoint.h"

#include "Engine/World.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	TArray<ASprungWheel*> Wheels;

	for (USceneComponent* Child : Children)
	{
		USuspensionSpawnPoint* SpawnPoint = Cast<USuspensionSpawnPoint>(Child);
		
		if (SpawnPoint != nullptr)
		{
			Wheels.Add(SpawnPoint->GetWheel());
		}
	}

	return Wheels;
}


void UTankTrack::DriveTrack(float Throttle)
{
	float ForceMagnitude = FMath::Clamp(Throttle, -1.F, +1.F) * MaxDrivingForce;

	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForceMagnitudePerWheel = ForceMagnitude / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForceMagnitudePerWheel);
	}
}

