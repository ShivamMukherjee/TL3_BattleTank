// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	this->AimingComponent = this->GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(this->AimingComponent))
	{
		return;
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	APawn* PlayerTank = this->GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && this->GetPawn()))
	{
		return;
	}

	this->MoveToActor(PlayerTank, this->AcceptanceRadius);
	this->AimingComponent->AimAt(PlayerTank->GetActorLocation());
	this->AimingComponent->Fire();
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank))
		{
			return;
		}
		// subscribe to Tank's Death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::Disengage);
	}
}


void ATankAIController::Disengage()
{
	if (this->GetPawn())
	{
		this->GetPawn()->DetachFromControllerPendingDestroy();
	}
}
