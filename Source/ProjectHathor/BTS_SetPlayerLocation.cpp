// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SetPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectHathor/HathorChraracter.h"

UBTS_SetPlayerLocation::UBTS_SetPlayerLocation()
{
	NodeName = TEXT("Update Player Location");

}

void UBTS_SetPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AHathorChraracter* PlayerCharacter = Cast<AHathorChraracter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerCharacter);
}
