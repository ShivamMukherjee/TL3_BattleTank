// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Aids in finding the aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Game Over Options")
	void EnterSpectatorMode();
	virtual void EnterSpectatorMode_Implementation();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponentReference);

private:
	class UTankAimingComponent* AimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	// start aiming barrel to fire through crosshair in the world
	void AimTowardsCrosshair();

	bool GetCrosshairTraceHit(FHitResult& Hit) const;

	void SetPawn(APawn* InPawn);
};
