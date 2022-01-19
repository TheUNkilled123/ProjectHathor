// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetPlayerLocation.generated.h"

UCLASS()
class PROJECTHATHOR_API UBTS_SetPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTS_SetPlayerLocation();

private:

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
