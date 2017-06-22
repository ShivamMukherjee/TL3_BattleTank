// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintSpawnableComponent, Category = "Setup")
	class UTankAimingComponent* AimingComponent = nullptr;

	// distance of approach of AI tank till it opens fire on  player
	float AcceptanceRadius = 3000.0;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
