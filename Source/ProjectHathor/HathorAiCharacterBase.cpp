// Fill out your copyright notice in the Description page of Project Settings.


#include "HathorAiCharacterBase.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
AHathorAiCharacterBase::AHathorAiCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentValue = 1.f;

	Health = DefaultHealth;
}

// Called when the game starts or when spawned
void AHathorAiCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	bIntroComplete = false;
	UE_LOG(LogTemp, Warning, TEXT("New value: %f"), currentValue);

	thisWorld = GetWorld();
}

// Called every frame
void AHathorAiCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIntroComplete)
	{
		animateIntro(DeltaTime);
	}

}

void AHathorAiCharacterBase::animateIntro(float DeltaTime)
{
	newValue = FMath::FInterpTo(currentValue, 0.f, DeltaTime, appearSpeed);

	UKismetMaterialLibrary::SetScalarParameterValue(thisWorld, materialCollection, TEXT("Dissolve"), newValue);
	currentValue = newValue;
	
	if (FMath::IsNearlyEqual(newValue, 0.f))
	{
		UE_LOG(LogTemp, Warning, TEXT("GETERDONEEEEEEEEEEEE"));
		bIntroComplete = true;
	}
}

float AHathorAiCharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0.f)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(thisWorld, materialCollection, TEXT("Dissolve"), 1.f);
		bIsDead = true;
	}
	return Damage;
}