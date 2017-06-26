// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

/**
 * Represents the Tank in the game
 */
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called by Engine when actor takes damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamagaEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100.0;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth = StartingHealth;
};
