// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeAngularSpeed)
{
	// move barrel the right amount in this frame
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f, Barrel->Elevate() called. Speed: %f"), Time, RelativeAngularSpeed);

	// given elevation speed and tick
}
