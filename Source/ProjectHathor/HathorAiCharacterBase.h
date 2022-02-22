// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HathorAiCharacterBase.generated.h"

UCLASS()
class PROJECTHATHOR_API AHathorAiCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHathorAiCharacterBase();

	UPROPERTY(EditAnywhere, Category = "Material Collection")
	UMaterialParameterCollection* materialCollection;

	UPROPERTY(EditAnywhere)
	bool bIsEnemy;

	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float appearSpeed = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackRange01 = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackRange02 = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float moveUseCooldown = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float conditionCooldown = 5.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bIntroComplete = false;

	float currentValue, newValue;
	float Health;
	bool bIsDead = false;

	void animateIntro(float DeltaTime);

	UWorld* thisWorld;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
