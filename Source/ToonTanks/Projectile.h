// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Misc/DateTime.h" 
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
	 UStaticMeshComponent* ProjectileMesh;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
	 class UProjectileMovementComponent* ProjectileMovementComponent;
	 

	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Components", meta = (AllowPrivateAccess = "true"))
	 float Damage = 50.f;

	 UFUNCTION()
	 void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComponent, FVector NormalImpulse,const FHitResult& Hit);

	 UPROPERTY(EditAnywhere, Category = "Properties|Combat", meta = (AllowPrivateAccess = "true"))
	 class UParticleSystem* HitParticles;

	 UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties|Combat", meta = (AllowPrivateAccess = "true"))
	 class UParticleSystemComponent* TrailParticles;
	 UPROPERTY(EditAnywhere, Category = "Properties|Combat")
	 class USoundBase* LaunchSound;
	 UPROPERTY(EditAnywhere, Category = "Properties|Combat")
	 class USoundBase* HitSound;

	 UPROPERTY(EditAnywhere, Category = "Properties|Combat")
	 TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
