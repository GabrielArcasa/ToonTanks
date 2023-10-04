// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector Target);

	void Fire();
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category ="Properties|Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties|Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, Category = "Properties|Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Properties|Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
