// Copyright (c) Shivam Mukherjee 2018

#include "BattleTank.h"
#include "SprungWheel.h"

#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;
	
	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{TEXT("Spring")});
	InitStringConstraint();

	AxleToWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName{TEXT("AxleToWheelConstraint")});
	InitAxleToWheelConstraint();

	Wheel = CreateDefaultSubobject<USphereComponent>(FName{TEXT("Wheel")});
	InitWheel();

	Axle = CreateDefaultSubobject<USphereComponent>(FName{TEXT("Axle")});
	InitAxle();

	SetRootComponent(SpringConstraint);
	Axle->SetupAttachment(SpringConstraint);
	AxleToWheelConstraint->SetupAttachment(Axle);
	Wheel->SetupAttachment(Axle);
}

void ASprungWheel::InitStringConstraint()
{
	SpringConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.F);
	SpringConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.F);
	SpringConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 100.F);

	SpringConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.F);
	SpringConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.F);
	SpringConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.F);

	SpringConstraint->SetLinearPositionDrive(false, false, true);
	SpringConstraint->SetLinearVelocityDrive(false, false, true);
	SpringConstraint->SetLinearDriveParams(500.F, 200.F, 0.F);
}

void ASprungWheel::InitAxleToWheelConstraint()
{
	AxleToWheelConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.F);
	AxleToWheelConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.F);
	AxleToWheelConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0.F);

	AxleToWheelConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.F);
	AxleToWheelConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.F);
	AxleToWheelConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.F);
}

void ASprungWheel::InitWheel()
{
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(NAME_None, 1000.F);
}

void ASprungWheel::InitAxle()
{
	Axle->SetMobility(EComponentMobility::Movable);
	Axle->SetSimulatePhysics(true);
	Axle->SetMassOverrideInKg(NAME_None, 1000.F);

	Axle->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Axle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (SpringConstraint && AxleToWheelConstraint && Wheel && Axle)
	{
		Wheel->SetNotifyRigidBodyCollision(true);
		Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

		SetupSpringConstraint();
	}
}

void ASprungWheel::SetupSpringConstraint()
{
	USceneComponent* SpawnPoint;

	if (GetAttachParentActor() != nullptr && (SpawnPoint = GetAttachParentActor()->GetRootComponent()) != nullptr)
	{
		SpringConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(SpawnPoint), NAME_None, Axle, NAME_None);
		AxleToWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetWorld()->TickGroup == ETickingGroup::TG_PostPhysics)
	{
		ForceMagnitudeThisFrame = 0;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	ForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Wheel->AddForce(ForceMagnitudeThisFrame * Axle->GetForwardVector());
}
