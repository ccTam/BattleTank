// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::TurretTurn(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, RawRotation, 0));
}