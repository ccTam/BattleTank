// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

class UTankBarrel; //Forward Declaration

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSec = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 30;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = -5;
	
};
