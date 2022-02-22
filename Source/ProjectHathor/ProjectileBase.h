// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ProjectileBase.generated.h"

class AAoeEffectActor;
UCLASS()
class PROJECTHATHOR_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHitBlocked(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AActor* MyOwner = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void FloorHit();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile attributes")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile attributes")
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, Category = "Projectile attributes")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Projectile attributes")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Projectile attributes")
	TSubclassOf<AAoeEffectActor> GroundActorToSpawn;


	UPROPERTY(EditAnywhere, Category = "Projectile attributes")
	float damageAmount = 10.f;

};
