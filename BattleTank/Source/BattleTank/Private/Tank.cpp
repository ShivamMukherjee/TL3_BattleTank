// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	this->CurrentHealth = this->StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageAmount = FMath::Clamp<int32>(FMath::RoundToInt(DamageAmount), 0, this->CurrentHealth);

	this->CurrentHealth -= DamageAmount;

	if (this->CurrentHealth <= 0)
	{
		this->OnDeath.Broadcast();
	}

	return DamageAmount;
}