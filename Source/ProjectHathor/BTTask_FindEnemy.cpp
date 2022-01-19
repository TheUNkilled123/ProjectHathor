// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "HathorAiCharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_FindEnemy::UBTTask_FindEnemy()
{
	NodeName = TEXT("Find Enemy");
}

EBTNodeResult::Type UBTTask_FindEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (BB == nullptr)
	{
		BB = OwnerComp.GetBlackboardComponent();
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHathorAiCharacterBase::StaticClass(), FoundActors);

	APawn* ThisPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ThisPawn->ActorHasTag(TEXT("Ally")))
	{
		for (AActor* Actor : FoundActors)
		{
			AHathorAiCharacterBase* CurrentActor = Cast<AHathorAiCharacterBase>(Actor);

			if (CurrentActor->ActorHasTag(TEXT("Enemy")))
			{
				if (closestDist == 0)
				{
					closestDist = ThisPawn->GetDistanceTo(Actor);
					closestActor = Actor;
				}
				else
				{
					currentDist = ThisPawn->GetDistanceTo(Actor);
					if (currentDist < closestDist)
					{
						closestDist = currentDist;
						closestActor = Actor;
					}
				}
			}
		}
	}
	else
	{
		for (AActor* Actor : FoundActors)
		{
			AHathorAiCharacterBase* CurrentActor = Cast<AHathorAiCharacterBase>(Actor);

			if (CurrentActor->ActorHasTag(TEXT("Ally")))
			{
				if (closestDist == 0)
				{
					closestDist = ThisPawn->GetDistanceTo(Actor);
					closestActor = Actor;
				}
				else
				{
					currentDist = ThisPawn->GetDistanceTo(Actor);
					if (currentDist < closestDist)
					{
						closestDist = currentDist;
						closestActor = Actor;
					}
				}
			}
		}
		numEnemy = numEnemy + 1;
	}
	currentActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	currentDist = ThisPawn->GetDistanceTo(currentActor);
	if (currentDist < closestDist)
	{
		closestDist = currentDist;
		closestActor = currentActor;
	}

	BB->SetValueAsObject(GetSelectedBlackboardKey(), currentActor);
	FoundActors.Empty();
	closestDist = 0;
	return EBTNodeResult::Succeeded;
}
