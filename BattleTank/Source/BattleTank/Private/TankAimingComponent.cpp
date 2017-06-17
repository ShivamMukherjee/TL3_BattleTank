// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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
	if (!this->Barrel || !this->Turret)
	{
		return;
	}

	FVector OutLaunchVelocity;

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		this->Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f
		, ESuggestProjVelocityTraceOption::DoNotTrace // comment out line to reproduce bug
	);

	if (bAimSolutionFound)
	{
		FRotator AimRotation = OutLaunchVelocity.Rotation();
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Can fire there! Yay."), Time);
		this->MoveBarrelTowards(AimRotation);
		this->MoveTurretTowards(AimRotation);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Can't fire there."), Time);
	}
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	this->Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	this->Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FRotator AimRotation)
{
	FRotator BarrelRotation = this->Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	this->Barrel->Elevate(DeltaRotation.Pitch);
}


void UTankAimingComponent::MoveTurretTowards(FRotator AimRotation)
{
	FRotator TurretRotation = this->Turret->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - TurretRotation;

	this->Turret->Rotate(DeltaRotation.Yaw);
}