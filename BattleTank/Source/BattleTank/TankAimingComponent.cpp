// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet) {
	this->Barrel = BarrelToSet;
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
		ESuggestProjVelocityTraceOption::TraceFullPath,
		true
	);

	if (bSPV) {
		auto AimDir = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDir.ToString());
		MoveBarrelTowards(AimDir);
	}
	DrawDebugLine(GetWorld(), Barrel->GetSocketLocation(FName("FirePos")), HitLoc, FColor::Red); 
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDir.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator:%s"), *DeltaRotator.ToString());
}