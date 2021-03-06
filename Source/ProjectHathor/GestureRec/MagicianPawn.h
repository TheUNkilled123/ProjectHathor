#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MagicianPawn.generated.h"

UCLASS()
class PROJECTHATHOR_API AMagicianPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shapes")
	TMap<FString, UClass*> ShapeMap;

public:
	AMagicianPawn();
	void SpawnShape(const FString &Name);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
