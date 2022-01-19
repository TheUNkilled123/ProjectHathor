// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FocusTarget.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectHathor/HathorAiCharacterBase.h"
#include "AIController.h"

UBTTask_FocusTarget::UBTTask_FocusTarget()
{
	NodeName = TEXT("Focus Target");
}

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	BB = OwnerComp.GetBlackboardComponent();
	ThisController = OwnerComp.GetAIOwner();
	
	TargetActor = Cast<AActor>(BB->GetValueAsObject(GetSelectedBlackboardKey()));

	ThisController->SetFocus(TargetActor, EAIFocusPriority::Gameplay);
	
	return EBTNodeResult::Succeeded;
}
