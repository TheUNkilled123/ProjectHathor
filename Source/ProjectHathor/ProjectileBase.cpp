// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component1"));
	ProjectileMovement->SetUpdatedComponent(ProjectileMesh);
	/*
	ProjectileMovement->InitialSpeed = initialSpeed;
	ProjectileMovement->ProjectileGravityScale = gravityScale;
	ProjectileMovement->bShouldBounce = bShouldProjectileBounce;
	ProjectileMovement->Bounciness = bounciness;
	ProjectileMovement->Velocity = projectileVelocity;
	ProjectileMovement->ProjectileGravityScale = gravityScale;
	ProjectileMovement->MaxSpeed = initialSpeed + 1000.f;
	*/

	InitialLifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);

	MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		MyOwner = this;
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		if (OtherActor->ActorHasTag("Floor"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Projectile hit floor!"));
			//Create area of effect
			FloorHit();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			Destroy();
		}
		else if(Cast<AController>(OtherActor->GetInstigatorController()) != nullptr)
		{
			UGameplayStatics::ApplyDamage(OtherActor, damageAmount, MyOwner->GetInstigatorController(), MyOwner, DamageType);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, GetActorLocation());
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			Destroy();
		}
	}

}
