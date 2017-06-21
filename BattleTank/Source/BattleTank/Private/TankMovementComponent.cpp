// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}

	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;

	// TODO prevent superposition of controls
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!this->LeftTrack || !this->RightTrack)
	{
		return;
	}

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!this->LeftTrack || !this->RightTrack)
	{
		return;
	}

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = this->GetOwner()->GetActorForwardVector().GetSafeNormal();

	// dot product of unit vectors is the cosine of the angle between them
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	this->IntendMoveForward(ForwardThrow);

	// cross product for the sine of said angle
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	this->IntendTurnRight(RightThrow);
}