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
	// +Up: +1, -Down: -1
	void Elevate(float RelativeAngularSpeed);
	
private:
	// degrees/s
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxAngularSpeed = 15.0; 

	// degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 40.0;

	// degrees
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0.0;

};
