// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

	APlayerController* GetPlayerController() const;

	bool bAlive = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire();
private:

	UPROPERTY(VisibleAnywhere, Category = "Properties|Components")
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Properties|Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Properties|Movement")
	float Speed = 4.f;

	UPROPERTY(EditAnywhere, Category = "Properties|Movement")
	float TurnRate = 4.f;

	void Move(float Value);

	void Turn(float Value);
	
	APlayerController* PlayerController;


	FDateTime FireAtTime ;
};
