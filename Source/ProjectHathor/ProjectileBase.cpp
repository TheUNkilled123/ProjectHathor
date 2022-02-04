// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component1"));
	ProjectileMovement->SetUpdatedComponent(ProjectileMesh);
	ProjectileMovement->InitialSpeed = initialSpeed;
	ProjectileMovement->ProjectileGravityScale = gravityScale;
	ProjectileMovement->bShouldBounce = bShouldProjectileBounce;
	ProjectileMovement->Bounciness = bounciness;
	ProjectileMovement->Velocity = projectileVelocity;
	ProjectileMovement->ProjectileGravityScale = gravityScale;
	ProjectileMovement->MaxSpeed = initialSpeed + 1000.f;
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
