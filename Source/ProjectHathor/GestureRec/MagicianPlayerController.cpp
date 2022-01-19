#include "ProjectHathor/GestureRec/MagicianPlayerController.h"
#include "ProjectHathor/GestureRec/MagicianPawn.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"
#include "Runtime/Engine/Classes/Engine/RendererSettings.h"
#include "ProjectHathor/HathorChraracter.h"

AMagicianPlayerController::AMagicianPlayerController()
{

	bCanPaint = false;

	Recognizer = new FUnistrokeRecognizer();

	static ConstructorHelpers::FObjectFinder<UDataTable> UnistrokeTemplatesTable(TEXT("DataTable'/Game/DataTables/Templates.Templates'"));
	
	if (UnistrokeTemplatesTable.Succeeded())
	{
		UnistrokeTable = UnistrokeTemplatesTable.Object;
		LoadTemplates();
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> TrainWidgetClassRef(TEXT("/Game/Blueprints/Widgets/WBP_Train"));
	TrainWidgetClass = TrainWidgetClassRef.Class;

	static ConstructorHelpers::FClassFinder<UPaintWidget> PaintWidgetClassRef(TEXT("/Game/Blueprints/Widgets/WBP_Paint"));
	PaintWidgetClass = PaintWidgetClassRef.Class;

}

void AMagicianPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Create Paint Widget
	PaintWidget = CreateWidget<UPaintWidget>(this, PaintWidgetClass);
	if (PaintWidget != nullptr)
	{
		PaintWidget->AddToViewport();
		PaintWidget->SetVisibility(ESlateVisibility::Hidden);
	}
		
	// Create Train Widget
	TrainWidget = CreateWidget<UUserWidget>(this, TrainWidgetClass);
	if (TrainWidget != nullptr)
	{
		TrainWidget->AddToViewport();
		HideTrainWidget();
	}

	/*FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputMode.SetHideCursorDuringCapture(true);
	bShowMouseCursor = false;

	SetInputMode(InputMode);*/

	IsTraining = false;

	CurrentAction = Action::Idle;

	InputComponent->BindAction("PaintButton", IE_Pressed, this, &AMagicianPlayerController::PressedToPaint);
	InputComponent->BindAction("PaintButton", IE_Released, this, &AMagicianPlayerController::ReleasedToPaint);	


	InputComponent->BindAction("TogglePaint", IE_Released, this, &AMagicianPlayerController::toggleCanvas);
}

void AMagicianPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//PAINTING LOGIC(Painting in ui and for recognizer which is called when paint button is released)
	if (CurrentAction == Action::Paint)
	{
		const TArray<FVector2D> Points = PaintWidget->GetPoints();
		float MouseX = 0.0f;
		float MouseY = 0.0f;

		GetMousePosition(MouseX, MouseY);

		const FVector2D MousePoint = FVector2D(MouseX, MouseY);
		const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));		
		const FVector2D ScaledPoint = MousePoint / viewportScale;
		const FVector2D LastPoint = Points.Num() > 0 ? Points.Last() : ScaledPoint;
		const bool IsNewPoint = !LastPoint.Equals(ScaledPoint, 1.0f);

		if (Points.Num() == 0 || (Points.Num() > 0 && IsNewPoint))
		{
			PaintWidget->AddPoint(ScaledPoint);
		}
	}
}

//SETTING PAINTING ACTION
void AMagicianPlayerController::PressedToPaint()
{
	if (bCanPaint && CurrentAction != Action::Train)
		PaintWidget->RemoveAllPoints();
		CurrentAction = Action::Paint;
}
//SETTING STOP-PAINT-RECOGNIZE ACTION
void AMagicianPlayerController::ReleasedToPaint()
{
	if (bCanPaint && CurrentAction == Action::Paint)
		CurrentAction = IsTraining ? Action::Train : Action::Recognize;
	
	switch (CurrentAction)
	{
		case Action::Recognize:
			Spell();
			break;
		case  Action::Train:
			if (PaintWidget->GetPoints().Num() > 2)
				ShowTrainWidget();
			break;
		default:
			break;
	}		
}

void AMagicianPlayerController::Spell()
{
	TArray<FVector2D>CurrentPoints = PaintWidget->GetPoints();
	FUnistrokeResult Result = Recognizer->Recognize(CurrentPoints, false);

	if (Result.Score < 0.8f)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No Magic", true, FVector2D(2, 2));
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Result.Name, true, FVector2D(2, 2));

		//TODO: PUT CUSTOM CODE HERE TEEHEE

		/*AMagicianPawn* MagicianaPawn = Cast<AMagicianPawn>(GetPawn());
		MagicianaPawn->SpawnShape(Result.Name);
		*/

		AHathorChraracter* HathorChar = Cast<AHathorChraracter>(GetCharacter());
		HathorChar->SpawnShape(Result.Name);

	}

	PaintWidget->RemoveAllPoints();

	for (int i = 0; i < CurrentPoints.Num(); i++)
	{
		PaintWidget->RandomiseColors();
		PaintWidget->AddPoint(CurrentPoints[i]);
	}

	CurrentAction = Action::Idle;
}

//DO SHTI LIEK DIS TO STOP THE ZOOM ZOOM OF CAM WHILE DOODLE DOODLE ON PAPER
//DO SHTI LIEK DIS TO STOP THE ZOOM ZOOM OF CAM WHILE DOODLE DOODLE ON PAPER
//DO SHTI LIEK DIS TO STOP THE ZOOM ZOOM OF CAM WHILE DOODLE DOODLE ON PAPER
//DO SHTI LIEK DIS TO STOP THE ZOOM ZOOM OF CAM WHILE DOODLE DOODLE ON PAPER

void AMagicianPlayerController::toggleCanvas()
{
	if (bShowMouseCursor)
	{
		//DO SHTI LIEK DIS TO STOP THE ZOOM ZOOM OF CAM WHILE DOODLE DOODLE ON PAPER
		bShowMouseCursor = false;
		PaintWidget->ChangeVisibility(ESlateVisibility::Hidden);
		InputComponent->bBlockInput = false;
		bCanPaint = false;
		PaintWidget->RemoveAllPoints();
		CurrentAction = Action::Idle;
	}
	else
	{
		bShowMouseCursor = true;
		PaintWidget->ChangeVisibility(ESlateVisibility::Visible);
		InputComponent->bBlockInput = true;
		bCanPaint = true;
	}
}

void AMagicianPlayerController::LoadTemplates()
{
	if (UnistrokeTable != nullptr)
	{
		const FString ContextString = "Templates";
		TArray<FUnistrokeDataTable*> Rows;

		UnistrokeTable->GetAllRows<FUnistrokeDataTable>(ContextString, Rows);

		for (int i = 0; i < Rows.Num(); i++)
		{
			Recognizer->AddTemplate((*Rows[i]).Name, (*Rows[i]).Points);
		}
	}
}

void AMagicianPlayerController::TrainMode(const bool Is)
{
	IsTraining = Is;

	if (IsTraining)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Train mode is ON", true, FVector2D(2, 2));
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Train mode is OFF", true, FVector2D(2, 2));
	}
}

void AMagicianPlayerController::AddTemplateToDataTable(const FString Name)
{
	FUnistrokeDataTable DataRow;
	
	DataRow.Name = Name;
	DataRow.Points = PaintWidget->GetPoints();
	
	const FString ContextString = "Templates";
	TArray<FUnistrokeDataTable*> Rows;
	
	UnistrokeTable->GetAllRows<FUnistrokeDataTable>(ContextString, Rows);
	
	int RowNum = Rows.Num() + 1;
	
	UnistrokeTable->AddRow(FName(*FString::FromInt(RowNum)), DataRow);
	
	Recognizer->AddTemplate(Name, PaintWidget->GetPoints());		
	
	HideTrainWidget();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "New Gesture was added", true, FVector2D(2, 2));
}

void AMagicianPlayerController::ShowTrainWidget()
{
	if (TrainWidget != nullptr)
	{
		TrainWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentAction = Action::Train;
	}
}

void AMagicianPlayerController::HideTrainWidget()
{
	if (TrainWidget != nullptr)
	{		
		PaintWidget->RemoveAllPoints();
		TrainWidget->SetVisibility(ESlateVisibility::Hidden);
		CurrentAction = Action::Idle;
	}
}
