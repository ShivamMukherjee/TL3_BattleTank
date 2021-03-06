// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if ((AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}

	FHitResult OutHit;

	if (GetCrosshairTraceHit(OutHit))
	{
		AimingComponent->AimAt(OutHit.ImpactPoint);
		AimingComponent->SetHitResult(OutHit);
	}
}


bool ATankPlayerController::GetCrosshairTraceHit(FHitResult& Hit) const
{
	// Viewport Size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D CrosshairPosition = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	return GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_Camera, false, Hit);

	// Draws a red line for debugging purposes
	//DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor(30, 40, 50));
}


void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!(PossessedTank))
		{
			return;
		}
		// subscribe to Tank's Death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::EnterSpectatorMode);
	}
}


void ATankPlayerController::EnterSpectatorMode_Implementation()
{
	if (GetPawn())
	{
		StartSpectatingOnly();
	}
}
