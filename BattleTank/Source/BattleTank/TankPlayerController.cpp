// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

// Called every frame
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possesing: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank> (GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) {
		return;
	}
	FVector HitLoc;
	if (GetSightRayHitLoc(HitLoc)) {
		GetControlledTank()->AimAt(HitLoc);
	}
}

bool ATankPlayerController::GetSightRayHitLoc(FVector & HitLoc) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLoc = FVector2D(ViewportSizeX*CrossHairXLoc, ViewportSizeY*CrossHairYLoc);
	FHitResult HitResult;
	//De-project the screen position of the crosshair to a world direction
	if (GetHitResultAtScreenPosition(ScreenLoc, ECollisionChannel::ECC_Visibility, false, HitResult)) {
		HitLoc = HitResult.Location;
		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);
		return true;
	}
	return false;
}