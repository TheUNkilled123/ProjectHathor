// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHATHOR_API UBTTask_FindEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_FindEnemy();

	int numEnemy = 0;

private:
	AActor* closestActor;
	AActor* currentActor;

	float closestDist;
	float currentDist;

	UBlackboardComponent* BB;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
