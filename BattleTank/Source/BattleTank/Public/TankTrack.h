// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and apply forces.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	// sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DriveTrack(float Throttle);
	
	// 40 ton tank with 1g acceleration, Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40e6F;

private:
	
	TArray<class ASprungWheel*> GetWheels() const;

};
