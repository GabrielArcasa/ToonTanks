// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h" 
#include "GameFramework/ProjectileMovementComponent.h" 
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h" 
#include "Sound/SoundBase.h"
#include "Camera/CameraShakeBase.h" 
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 50;
	ProjectileMovementComponent->MaxSpeed = 200;
	TrailParticles->SetupAttachment(ProjectileMesh);
	RootComponent = ProjectileMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	auto MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	};

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}


	}
		Destroy();
}

