// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HathorAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHATHOR_API AHathorAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AiBehavior;

protected:

	virtual void BeginPlay() override;

};
