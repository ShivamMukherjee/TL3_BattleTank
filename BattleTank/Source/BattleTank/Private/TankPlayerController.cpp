// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	this->AimingComponent = Cast<ATank>(this->GetPawn())->FindComponentByClass<UTankAimingComponent>();

	if (ensure(this->AimingComponent))
	{
		FoundAimingComponent(this->AimingComponent);
	}
	else
	{
		return;
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation = FVector(0);

	if (GetCrosshairTraceHit(HitLocation))
	{
		this->AimingComponent->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetCrosshairTraceHit(FVector& HitLocation) const
{
	// Viewport Size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	bool bHit;
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FHitResult HitResult;

	bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_WorldStatic, false, HitResult);

	if (bHit)
	{
		HitLocation = HitResult.ImpactPoint;
	}

	// Draws a red line for debugging purposes
	//DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor(30, 40, 50));

	return bHit;
}