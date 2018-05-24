// Copyright (c) Shivam Mukherjee 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SuspensionSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USuspensionSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USuspensionSpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FORCEINLINE class ASprungWheel* GetWheel() const { return Wheel; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ASprungWheel> SprungWheelBP;
	
	ASprungWheel* Wheel;
};
