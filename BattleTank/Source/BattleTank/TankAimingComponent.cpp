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

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
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
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDir.ToString());
	}
	DrawDebugLine(GetWorld(), Barrel->GetSocketLocation(FName("FirePos")), HitLoc, FColor::Red); 
}