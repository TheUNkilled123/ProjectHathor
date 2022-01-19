// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHATHOR_API UBTService_FindEnemy : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_FindEnemy();

protected:
	//virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
