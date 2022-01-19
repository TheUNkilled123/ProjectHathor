#pragma once

#include "CoreMinimal.h"
#include "UnistrokeRecognizer.h"
#include "PaintWidget.h"
#include "UnistrokeDataTable.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "MagicianPlayerController.generated.h"

enum Action { Idle, Paint, Recognize, Train };

UCLASS()
class PROJECTHATHOR_API AMagicianPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Exec)
	void TrainMode(const bool Is);
		
public:	
	AMagicianPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void ShowTrainWidget();
	void HideTrainWidget();
	void AddTemplateToDataTable(const FString Name);

private:
	void PressedToPaint();
	void ReleasedToPaint();
	void LoadTemplates();
	virtual void Spell();

	void toggleCanvas();

private:
	UDataTable* UnistrokeTable;
	UPaintWidget* PaintWidget;
	UUserWidget* TrainWidget;
	TSubclassOf<UPaintWidget> PaintWidgetClass;
	TSubclassOf<UUserWidget> TrainWidgetClass;
	FUnistrokeRecognizer* Recognizer;		
	int CurrentAction;
	bool IsTraining;
	bool bCanPaint;
	
};
