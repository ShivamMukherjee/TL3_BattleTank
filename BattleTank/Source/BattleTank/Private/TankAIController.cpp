// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(this->GetPawn());

	if (!PlayerTank)
	{
		return;
	}

	// TODO move towards player
	this->MoveToActor(PlayerTank, this->AcceptanceRadius);

	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	ControlledTank->Fire();
}
