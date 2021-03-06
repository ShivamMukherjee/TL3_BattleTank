// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeAngularSpeed)
{
	RelativeAngularSpeed = FMath::Clamp<float>(RelativeAngularSpeed, -1, +1);
	float RotationChange = RelativeAngularSpeed * MaxAngularSpeed * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
