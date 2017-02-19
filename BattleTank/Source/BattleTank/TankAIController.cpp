// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Can't find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller[%s] found player tank: %s"), *(GetControlledTank()->GetName()), *(PlayerTank->GetName()));
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	auto PlayerTank = Cast<ATank> (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto CurrentTime = GetWorld()->GetTimeSeconds();
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
		GetControlledTank()->Fire();
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


