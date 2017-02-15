// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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
		UE_LOG(LogTemp, Warning, TEXT("HitLoc: %s"), *HitLoc.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLoc(FVector & HitLoc) const {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLoc = FVector2D(ViewportSizeX*CrossHairXLoc, ViewportSizeY*CrossHairYLoc);
	//De-project the screen position of the crosshair to a world direction
	FVector LookDir;
	if (GetLookDir(ScreenLoc, LookDir)) {
		UE_LOG(LogTemp, Warning, TEXT("LookDir: %s"), *LookDir.ToString());
	}
	return true;
}

bool ATankPlayerController::GetLookDir(FVector2D ScreenLoc, FVector& LookDir) const{
	FVector CameraWorldLoc;
	return DeprojectScreenPositionToWorld(
		ScreenLoc.X, 
		ScreenLoc.Y, 
		CameraWorldLoc, 
		LookDir
	);
}