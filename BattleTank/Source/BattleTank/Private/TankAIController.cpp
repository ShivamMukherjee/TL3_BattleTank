// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!(AimingComponent))
	{
		return;
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!(PlayerTank && GetPawn()))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!PossessedTank)
		{
			return;
		}
		// subscribe to Tank's Death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::Disengage);
	}
}


void ATankAIController::Disengage()
{
	if (GetPawn())
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}
