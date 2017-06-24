// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	this->ApplySidewaysForce();
}


void UTankTrack::ApplySidewaysForce()
{

	// calculate slippage speed
	float SlippageSpeed = FVector::DotProduct(this->GetRightVector(), this->GetComponentVelocity());

	// work out acceleration correction
	float DeltaTime = this->GetWorld()->GetDeltaSeconds();
	FVector CorrectionAccleration = SlippageSpeed / DeltaTime * this->GetRightVector();

	// calculate and apply sideways force
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAccleration) / 2; // for each track

	TankRoot->AddForce(-CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = this->GetForwardVector() * Throttle * this->MaxDrivingForce;
	FVector ForceLocation = this->GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

