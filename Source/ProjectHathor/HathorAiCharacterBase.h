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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool bIsEnemy;

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

private:
	bool bIntroComplete = false;

	float currentValue,newValue;

	void animateIntro(float DeltaTime);

};
