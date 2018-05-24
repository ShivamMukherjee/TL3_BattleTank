// Copyright (c) Shivam Mukherjee 2018

#include "BattleTank.h"
#include "SprungWheel.h"
#include "SuspensionSpawnPoint.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USuspensionSpawnPoint::USuspensionSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	if (Wheel == nullptr)
	{
		return;
	}
}


// Called when the game starts
void USuspensionSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// To ensure that the sprung wheel actor is spawned properly, we use SpawnActorDeferred
	Wheel = GetWorld()->SpawnActorDeferred<ASprungWheel>(SprungWheelBP, GetComponentTransform());
	
	if (Wheel != nullptr)
	{
		Wheel->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		UGameplayStatics::FinishSpawningActor(Wheel, GetComponentTransform());
	}
}
