#include "ProjectHathor/GestureRec/PaintWidget.h"

int32 UPaintWidget::NativePaint(const FPaintArgs &Args, const FGeometry &AllottedGeometry, const FSlateRect &MyCullingRect, FSlateWindowElementList &OutDrawElements, int32 LayerId, const FWidgetStyle &InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	UWidgetBlueprintLibrary::DrawLines(Context, Points, colorToDraw, true, 10.0f);

	return LayerId + 1;
}


void UPaintWidget::ChangeVisibility(ESlateVisibility InVisibility)
{
	PlayAnims(InVisibility);
}

TArray<FVector2D> UPaintWidget::GetPoints()
{
	return Points;
}

void UPaintWidget::AddPoint(const FVector2D &Point)
{
	Points.Add(Point);
}

void UPaintWidget::RemoveAllPoints()
{
	Points.Empty();
}

void UPaintWidget::RandomiseColors()
{
	colorToDraw = FLinearColor::MakeRandomColor();
}

