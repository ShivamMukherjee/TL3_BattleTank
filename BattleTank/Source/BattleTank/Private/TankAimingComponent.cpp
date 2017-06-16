// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!this->Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		this->Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed
	);

	if (bAimSolutionFound)
	{
		this->MoveBarrelTowards(OutLaunchVelocity.Rotation());
	}
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	this->Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FRotator AimRotation)
{
	FRotator BarrelRotation = this->Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	this->Barrel->Elevate(5); // TODO refactor magic number
}