// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	UE_LOG(BTCtorLog, Warning, TEXT("%s: verify"), *this->GetName());

	// Valid if not added via Blueprint
	//this->TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName(TEXT("Aiming Component")));
	//this->TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName(TEXT("Movement Component")));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(BTBeginPlayLog, Warning, TEXT("%s: verify"), *this->GetName());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	UTankAimingComponent* TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

	if (!ensure(TankAimingComponent))
	{
		return;
	}

	TankAimingComponent->AimAt(HitLocation, this->LaunchSpeed);
}


void ATank::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	UTankAimingComponent* TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

	if (!ensure(TankAimingComponent))
	{
		return;
	}

	TankAimingComponent->Initialise(BarrelToSet, TurretToSet);
}


void ATank::Fire()
{
	if (!ensure(this->Barrel))
	{
		return;
	}

	bool bIsReloaded = (FPlatformTime::Seconds() - this->LastFireTime) > this->ReloadTime;

	if (bIsReloaded)
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