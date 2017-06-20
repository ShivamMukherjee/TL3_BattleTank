// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: %s Throttle: %f"), GetWorld()->GetTimeSeconds(), *this->GetName(), Throttle);

	FVector ForceApplied = this->GetForwardVector() * Throttle * this->MaxDrivingForce;
	FVector ForceLocation = this->GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

