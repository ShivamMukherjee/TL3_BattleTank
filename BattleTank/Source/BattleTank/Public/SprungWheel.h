// Copyright (c) Shivam Mukherjee 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupSpringConstraint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPhysicsConstraintComponent* SpringConstraint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPhysicsConstraintComponent* AxleToWheelConstraint;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* Wheel;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* Axle;

	float ForceMagnitudeThisFrame;

	void InitStringConstraint();

	void InitAxleToWheelConstraint();

	void InitWheel();

	void InitAxle();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
