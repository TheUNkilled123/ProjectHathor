// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AoeEffectActor.generated.h"

UCLASS()
class PROJECTHATHOR_API AAoeEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAoeEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DoDamage();

	AActor* MyOwner = nullptr;
	FTimerHandle DamageTimer;

	bool bCanDamage = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* ActorCollision;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 10.f;

	UPROPERTY(EditAnywhere)
	float DamageDelay = 2.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageType;

};
