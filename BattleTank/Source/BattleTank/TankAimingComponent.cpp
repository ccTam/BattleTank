// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet) {
	this->Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet) {
	this->Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLoc, float LaunchSpeed) {
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLoc = Barrel->GetSocketLocation(FName("FirePos"));
	bool bSPV = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLoc,
		HitLoc,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bSPV) {
		auto AimDir = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDir.ToString());
		MoveBarrelTowards(AimDir);
		MoveTurretTowards(AimDir);
	}
	DrawDebugLine(GetWorld(), Barrel->GetSocketLocation(FName("FirePos")), HitLoc, FColor::Red); 
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator:%s"), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDir) {
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator:%s"), *DeltaRotator.ToString());
	Turret->TurretTurn(DeltaRotator.Yaw);
}