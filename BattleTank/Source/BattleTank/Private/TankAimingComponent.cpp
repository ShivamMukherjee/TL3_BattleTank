// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!(BarrelToSet && TurretToSet))
	{
		return;
	}

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	else 
	{
		if (IsBarrelMoving())
		{
			FiringState = EFiringState::Aiming;
		}
		else
		{
			FiringState = EFiringState::Locked;
		}
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!(Barrel && Turret))
	{
		return;
	}

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
		HitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // comment out line to reproduce bug
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>{GetOwner()},
		false
	);

	if (bAimSolutionFound)
	{
		MoveBarrelTowards(LaunchVelocity.Rotation());
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!(Barrel))
	{
		return false;
	}

	return !Barrel->GetForwardVector().Equals(LaunchVelocity.GetSafeNormal(), 0.01);
}

void UTankAimingComponent::MoveBarrelTowards(FRotator AimRotation)
{
	if (!(Barrel && Turret))
	{
		return;
	}

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(FMath::Abs(DeltaRotation.Yaw) < 180 ? DeltaRotation.Yaw : 180 - DeltaRotation.Yaw);
}


void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!(Barrel && ProjectileBlueprint))
		{
			return;
		}

		this
		->GetWorld()
		->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			Barrel->GetSocketRotation(FName(TEXT("Projectile"))))
		->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}