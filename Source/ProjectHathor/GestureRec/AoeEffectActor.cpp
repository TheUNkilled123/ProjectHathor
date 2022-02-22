// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectHathor/GestureRec/AoeEffectActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AAoeEffectActor::AAoeEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (ActorCollision == nullptr)
	{
		ActorCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
	}

	RootComponent = ActorCollision;
}

// Called when the game starts or when spawned
void AAoeEffectActor::BeginPlay()
{
	Super::BeginPlay();

	ActorCollision->OnComponentBeginOverlap.AddDynamic(this, &AAoeEffectActor::OnOverlap);

	MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		MyOwner = this;
	}
	
	bCanDamage = true;
}

// Called every frame
void AAoeEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAoeEffectActor::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != nullptr && bCanDamage)
	{
		DoDamage();
	}

}

void AAoeEffectActor::DoDamage()
{
	bCanDamage = true;
	TArray<AActor*> OverlappingActors;
	ActorCollision->GetOverlappingActors(OverlappingActors);
	if (!OverlappingActors.Num() == 0)
	{
		for (int i = 0; i <= OverlappingActors.Num() - 1; i++)			{
			UGameplayStatics::ApplyDamage(OverlappingActors[i], BaseDamage, MyOwner->GetInstigatorController(), this, DamageType);
			UE_LOG(LogTemp, Warning, TEXT("Damaging!"));
		}
		bCanDamage = false;
		GetWorldTimerManager().SetTimer(DamageTimer, this, &AAoeEffectActor::DoDamage, DamageDelay, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor no longer overlapping!"));
	}
}

