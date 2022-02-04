// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectileBase.generated.h"


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

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* HitParticle;



	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* LaunchSound;


	//Default projectile values
	UPROPERTY(EditAnywhere)
	float initialSpeed = 1000.f;
	UPROPERTY(EditAnywhere)
	float gravityScale = 1.f;
	UPROPERTY(EditAnywhere)
	float bounciness = 10.f;
	UPROPERTY(EditAnywhere, Category = "Damage")
	float damageAmount = 10.f;

	UPROPERTY(EditAnywhere)
	bool bShouldProjectileBounce = false;

	UPROPERTY(EditAnywhere)
	FVector projectileVelocity = FVector(0.f, 0.f, 200.f);
};
