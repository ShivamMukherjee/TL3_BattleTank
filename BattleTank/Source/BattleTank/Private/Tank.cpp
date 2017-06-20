// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
	
	// Valid if not added via Blueprint
	//this->TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName(TEXT("Movement Component")));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	this->TankAimingComponent->AimAt(HitLocation, this->LaunchSpeed);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	this->TankAimingComponent->SetBarrelReference(BarrelToSet);
	this->Barrel = BarrelToSet;
}


void ATank::SetTurretReference(UTankTurret* Turret)
{
	this->TankAimingComponent->SetTurretReference(Turret);
}


void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - this->LastFireTime) > this->ReloadTime;

	if (this->Barrel && bIsReloaded)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			this->Barrel->GetSocketLocation(FName(TEXT("Projectile"))),
			this->Barrel->GetSocketRotation(FName(TEXT("Projectile")))
			);

		Projectile->LaunchProjectile(this->LaunchSpeed);
		this->LastFireTime = FPlatformTime::Seconds();
	}

}