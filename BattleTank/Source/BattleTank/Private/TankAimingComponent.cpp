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


void UTankAimingComponent::BeginPlay()
{
	this->LastFireTime = FPlatformTime::Seconds();
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


void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - this->LastFireTime) < this->ReloadTime)
	{
		this->FiringState = EFiringState::Reloading;
		
	}
	else
	{
		if (this->IsBarrelMoving())
		{
			this->FiringState = EFiringState::Aiming;
		}
		
		UPrimitiveComponent* HitComponent = this->HitResult.GetComponent();

		if (!HitComponent)
		{
			return;
		}

		UClass* HitObjectClass = HitComponent->GetClass();
		UClass* ThisClass = this->GetOwner()->GetRootComponent()->GetClass();

		if (HitObjectClass == ThisClass)
		{
			this->FiringState = EFiringState::Locked;
		}
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(this->Barrel && this->Turret))
	{
		return;
	}

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		this->LaunchVelocity,
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
		this->MoveBarrelTowards(this->LaunchVelocity.Rotation());
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(this->Barrel))
	{
		return false;
	}

	return !this->Barrel->GetForwardVector().Equals(this->LaunchVelocity, 0.01);
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
	if (this->FiringState != EFiringState::Reloading)
	{
		if (!ensure(this->Barrel && this->ProjectileBlueprint))
		{
			return;
		}

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