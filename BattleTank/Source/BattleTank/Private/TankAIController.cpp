// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PlayerTank = this->GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController could not find the Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has found the player tank: %s"), *PlayerTank->GetName());
	}
}


void ATankAIController::Tick(float DeltaTime)
{
	ATank* PlayerTank = this->GetPlayerTank();

	if (PlayerTank)
	{
		// TODO move towards player

		// aim towards player
		this->GetControlledTank()->AimAt(this->GetPlayerTank()->GetActorLocation());

		// TODO fire at player
	}
}


ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
