// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamagaEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = FMath::Clamp<float>(DamageAmount, 0, this->CurrentHealth);

	UE_LOG(BTInfoLog, Warning, TEXT("DamageAmount: %f, Damage Applied: %f"), DamageAmount, DamageToApply);

	return DamageToApply;
}