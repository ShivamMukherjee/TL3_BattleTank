// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!this->Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	FRotator AimRotation;

	bool bAimSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		this->Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed
	);

	if (bAimSolutionFound)
	{
		AimRotation = OutLaunchVelocity.Rotation();
		UE_LOG(LogTemp, Warning, TEXT("Rotation needed for shot: %s"), *AimRotation.ToString());
	}
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	this->Barrel = BarrelToSet;
}


void UTankAimingComponent::MoveBarrelTowards(FRotator AimRotation)
{
	FRotator BarrelRotation = this->Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = AimRotation - BarrelRotation;
}