// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("Projectile Movement")));
	this->CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Collision Mesh")));
	this->LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Launch Blast")));
	this->ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("Impact Blast")));

	this->SetRootComponent(this->CollisionMesh);
	this->CollisionMesh->SetNotifyRigidBodyCollision(true);
	this->CollisionMesh->SetVisibility(false);

	this->LaunchBlast->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->ImpactBlast->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->ImpactBlast->bAutoActivate = false;

	if (!ensure(this->ProjectileMovement))
	{
		return;
	}

	this->ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	this->ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	this->ProjectileMovement->Activate();
}