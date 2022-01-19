// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHATHOR_API UBTTask_FocusTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_FocusTarget();

private:
	UBlackboardComponent* BB;

	AAIController* ThisController;

	AActor* TargetActor;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
