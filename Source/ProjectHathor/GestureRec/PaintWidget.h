#pragma once

#include "CoreMinimal.h"
#include "Math/Vector2D.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PaintWidget.generated.h"

UCLASS()
class PROJECTHATHOR_API UPaintWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual int32 NativePaint(const FPaintArgs &Args, const FGeometry &AllottedGeometry, const FSlateRect &MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle &InWidgetStyle, bool bParentEnabled) const override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnims(ESlateVisibility OutVisibility);

	void ChangeVisibility(ESlateVisibility InVisibility);

	TArray<FVector2D> GetPoints();
	void AddPoint(const FVector2D &Point);
	void RemoveAllPoints();
	void RandomiseColors();

	FLinearColor colorToDraw = FLinearColor::Red;

private:
	TArray<FVector2D> Points;
};
