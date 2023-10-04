// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h" 
#include "Tank.h"
#include "TimerManager.h"
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(InFireRange())
			RotateTurret(Tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr) return;

	if (InFireRange() && Tank->bAlive)
		Fire();
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}
	return false;
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
