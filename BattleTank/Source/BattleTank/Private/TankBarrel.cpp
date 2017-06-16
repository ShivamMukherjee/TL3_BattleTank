// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeAngularSpeed)
{
	// move barrel the right amount in this frame, given elevation speed and tick
	RelativeAngularSpeed = FMath::Clamp<>(RelativeAngularSpeed, -1.f, 1.f);
	float ElevationChange = RelativeAngularSpeed * this->MaxAngularSpeed * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::ClampAngle(RawNewElevation, this->MinElevation, this->MaxElevation);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}
