// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	//UPROPERTY(EditDefaultsOnly)
	//float LineTraceRange = 1000000.f; // 10km

	ATank* GetControlledTank() const;

	// start aiming barrel to fire through crosshair in the world
	void AimTowardsCrosshair();

	bool GetCrosshairTraceHit(FString& ObjectHit, FVector& HitLocation) const;

	//bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	//bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
