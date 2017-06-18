// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RelativeAngularSpeed)
{
	RelativeAngularSpeed = FMath::Clamp<>(RelativeAngularSpeed, -1.f, +1.f);
	float RotationChange = RelativeAngularSpeed * this->MaxAngularSpeed * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}