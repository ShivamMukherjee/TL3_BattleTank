// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeAngularSpeed)
{
	// move barrel the right amount in this frame
	float ElevationChange = RelativeAngularSpeed * this->MaxAngularSpeed * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp<>(RawNewElevation, this->MinElevation, this->MaxElevation);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

	// given elevation speed and tick
}
