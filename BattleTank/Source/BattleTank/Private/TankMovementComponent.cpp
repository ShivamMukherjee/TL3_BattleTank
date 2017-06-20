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

	UE_LOG(LogTemp, Warning, TEXT("Intend turn right: %f"), Throw);

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(-Throw);
}