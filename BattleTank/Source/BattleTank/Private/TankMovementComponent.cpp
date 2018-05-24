// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!(LeftTrackToSet && RightTrackToSet))
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

	// TODO prevent superposition of controls
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!(LeftTrack && RightTrack))
	{
		return;
	}

	LeftTrack->DriveTrack(Throw);
	RightTrack->DriveTrack(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!(LeftTrack && RightTrack))
	{
		return;
	}

	LeftTrack->DriveTrack(Throw);
	RightTrack->DriveTrack(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// dot product of unit vectors is the cosine of the angle between them
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	// cross product for the sine of said angle
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}