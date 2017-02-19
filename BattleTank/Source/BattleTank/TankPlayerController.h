// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//moving barrel to aim
	void AimTowardsCrosshair();
	bool GetSightRayHitLoc(FVector& HitLoc) const;
	UPROPERTY(EditAnywhere)
	float CrossHairXLoc = .5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLoc = .3333333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000;
};
