// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	this->AimingComponent = Cast<ATank>(this->GetPawn())->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaTime)
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerTank))
	{
		return;
	}

	this->MoveToActor(PlayerTank, this->AcceptanceRadius);

	this->AimingComponent->AimAt(PlayerTank->GetActorLocation());

	this->AimingComponent->Fire();
}
