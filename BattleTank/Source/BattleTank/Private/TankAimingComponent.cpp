// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(BTInfoLog, Warning, TEXT(__FUNCSIG__));
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(this->Barrel && this->Turret))
	{
		return;
	}

	FVector OutLaunchVelocity;

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		this->Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
		HitLocation,
		this->LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // comment out line to reproduce bug
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>{this->GetOwner()},
		false
	);

	if (bAimSolutionFound)
	{
		this->MoveBarrelTowards(OutLaunchVelocity.Rotation());
	}
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet))
	{
		return;
	}

	this->Barrel = BarrelToSet;
	this->Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FRotator AimRotation)
{
	if (!ensure(this->Barrel && this->Turret))
	{
		return;
	}

	FRotator BarrelRotation = this->Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;

	this->Barrel->Elevate(DeltaRotation.Pitch);
	this->Turret->Rotate(DeltaRotation.Yaw);
}


void UTankAimingComponent::Fire()
{
	if (!ensure(this->Barrel))
	{
		return;
	}

	bool bIsReloaded = (FPlatformTime::Seconds() - this->LastFireTime) > this->ReloadTime;

	if (bIsReloaded)
	{
		this
		->GetWorld()
		->SpawnActor<AProjectile>(
			this->ProjectileBlueprint,
			this->Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			this->Barrel->GetSocketRotation(FName(TEXT("Projectile"))))
		->LaunchProjectile(this->LaunchSpeed);

		this->LastFireTime = FPlatformTime::Seconds();
	}
}