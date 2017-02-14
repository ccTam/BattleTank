// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//moving barrel to aim
	void AimTowardsCrosshair();
	bool GetSightRayHitLoc(FVector &) const;
};
