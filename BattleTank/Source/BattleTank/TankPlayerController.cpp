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
	FHitResult HitResult;
	//De-project the screen position of the crosshair to a world direction
	if (GetHitResultAtScreenPosition(ScreenLoc, ECollisionChannel::ECC_Visibility, false, HitResult)) {
		HitLoc = HitResult.Location;
		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);
		return true;
	}
	//FVector LookDir;
	//if (GetLookDir(ScreenLoc, LookDir)) {
	//	UE_LOG(LogTemp, Warning, TEXT("LookDir: %s"), *LookDir.ToString());
	//	GetLookVectorHitLoc(LookDir, HitLoc);
	//}
	return false;
}

//bool ATankPlayerController::GetLookDir(FVector2D ScreenLoc, FVector& LookDir) const{
//	FVector CameraWorldLoc;
//	return DeprojectScreenPositionToWorld(
//		ScreenLoc.X, 
//		ScreenLoc.Y, 
//		CameraWorldLoc, 
//		LookDir
//	);
//}
//
//bool ATankPlayerController::GetLookVectorHitLoc(FVector LookDir, FVector& HitLoc) const{
//	FHitResult HitResult;
//	auto StartLoc = PlayerCameraManager->GetCameraLocation();
//	auto EndLoc = StartLoc + LookDir*LineTraceRange;
//	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECollisionChannel::ECC_Visibility)) {
//		return true;
//	} 
//	
//}	return false;