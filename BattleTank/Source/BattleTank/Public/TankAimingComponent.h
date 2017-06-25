// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
	NoAmmo,
	Reloading,
	Aiming,
	Locked
};


class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	FORCEINLINE void SetHitResult(FHitResult Hit) { this->HitResult = Hit; }

	FORCEINLINE EFiringState GetFiringState() const { return this->FiringState; }

	UFUNCTION(BlueprintCallable, Category = "Firing")
	FORCEINLINE int32 GetRoundsLeft() const { return this->RoundsLeft; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	FVector LaunchVelocity;

	FHitResult HitResult;

	// cm/s
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0;

	// seconds
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

	double LastFireTime = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AProjectile> ProjectileBlueprint = nullptr;

	bool IsBarrelMoving();

	void MoveBarrelTowards(FRotator AimRotation);

};