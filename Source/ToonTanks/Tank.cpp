// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h" 
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	FireAtTime = FDateTime::MinValue();
	PlayerController = Cast<APlayerController>(GetController()); // AController é Pai do APlayerController, então usamos Cast reverso para ter acesso aos Metodos do PlayerController
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		bool HasHit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		if (HasHit)
		{
			RotateTurret(HitResult.ImpactPoint);
		}
	}
}
void ATank::Fire()
{

	if ( FDateTime::Now() > FireAtTime + FDateTime(10000000))
	{
		FireAtTime = FDateTime::Now();
		Super::Fire();
	}
}
void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

APlayerController* ATank::GetPlayerController() const
{
	return PlayerController;
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector; // Cria um Vetor Zerado
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); // Valor do Axis * Velocidade * DeltaTime
	AddActorLocalOffset(DeltaLocation,true); // Move o Ator Localmente
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator; // Cria um Vetor Zerado
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this); // Valor do Axis * Velocidade * DeltaTime
	AddActorLocalRotation(DeltaRotation,true); // Move o Ator Localmente
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}
