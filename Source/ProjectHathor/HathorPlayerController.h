// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GestureRec/MagicianPlayerController.h"
#include "HathorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHATHOR_API AHathorPlayerController : public AMagicianPlayerController
{
	GENERATED_BODY()
	
public:
	AHathorPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
