// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxAngularVelocity = 20.f; // Sensible default: 20 degrees/s

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40.f; // Sensible default: 20 degrees/s

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.f; // Sensible default: 20 degrees/s

};
