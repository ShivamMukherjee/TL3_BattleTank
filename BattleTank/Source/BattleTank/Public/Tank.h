// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(class UTankBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(class UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	class UTankAimingComponent* TankAimingComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// in cm/s
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f; 

	// seconds
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	double LastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<class AProjectile> ProjectileBlueprint = nullptr;

	// Local barrel reference for spawning projectile
	class UTankBarrel* Barrel = nullptr;
	
};
