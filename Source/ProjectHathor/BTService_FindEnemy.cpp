// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HathorAiCharacterBase.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindEnemy::UBTService_FindEnemy()
{
	NodeName = TEXT("Find Enemy");
}

