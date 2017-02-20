// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle %f"), *Name, Throttle);
	auto ForceApplied = GetForwardVector() * Throttle * ThrottleMaxForce* 100;
	auto ForceLoc = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent> (GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLoc);

}


