// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

/**
 * Represents the Tank in the game
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	// Called by Engine when actor takes damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetHealthPercent() const { return static_cast<float>(this->CurrentHealth) / this->StartingHealth; }

	FTankDelegate OnDeath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100.0;

	int32 CurrentHealth;
};
