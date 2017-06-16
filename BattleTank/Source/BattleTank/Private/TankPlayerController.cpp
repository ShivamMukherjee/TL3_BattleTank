// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = this->GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController has possessed %s"), *ControlledTank->GetName());
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!this->GetControlledTank())
	{
		return;
	}

	FVector HitLocation = FVector(0);
	FString ObjectHit = "Nothing";

	if (GetCrosshairTraceHit(ObjectHit, HitLocation))
	{
		this->GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetCrosshairTraceHit(FString& ObjectHit, FVector& HitLocation) const
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
		ObjectHit = HitResult.GetActor()->GetName();
	}

	// Draws a red line for debugging purposes
	//DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor(30, 40, 50));

	return bHit;
}


//bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
//{
//	// Find crosshair position by de-projecting from screen pixels
//	int32 ViewportSizeX, ViewportSizeY;
//	GetViewportSize(ViewportSizeX, ViewportSizeY);
//
//	FVector2D ScreenLocation(ViewportSizeX * this->CrosshairXLocation, ViewportSizeY * this->CrosshairYLocation);
//	FVector OutLookDirection;
//
//	if (this->GetLookDirection(ScreenLocation, OutLookDirection))
//	{
//		// line trace along LookDirection
//		return this->GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
//	}
//
//	OutHitLocation = FVector(0);
//	return false;
//}
//
//
//bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
//{
//	FVector OutCameraWorldLocation;
//	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutCameraWorldLocation, OutLookDirection);
//}
//
//
//bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
//{
//	FHitResult Hit;
//	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
//
//	if (GetWorld()->LineTraceSingleByChannel(
//		Hit,
//		StartLocation,
//		StartLocation + LookDirection * this->LineTraceRange,
//		ECollisionChannel::ECC_Visibility
//	))
//	{
//		OutHitLocation = Hit.Location;
//		return true;
//	}
//	
//	return false;
//}