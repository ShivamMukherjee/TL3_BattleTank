// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// move barrel the right amount in this frame
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called. Speed: %f"), DegreesPerSecond);

	// given elevation speed and tick
}
