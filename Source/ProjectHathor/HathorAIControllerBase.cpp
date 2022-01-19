// Fill out your copyright notice in the Description page of Project Settings.


#include "HathorAIControllerBase.h"



void AHathorAIControllerBase::BeginPlay()
{

	Super::BeginPlay();

	if (AiBehavior != nullptr)
	{
		RunBehaviorTree(AiBehavior);
	}

}

void AHathorAIControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}