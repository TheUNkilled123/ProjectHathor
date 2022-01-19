// Fill out your copyright notice in the Description page of Project Settings.


#include "HathorChraracter.h"
#include "ProjectHathor/HathorAiCharacterBase.h"

// Sets default values
AHathorChraracter::AHathorChraracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHathorChraracter::SpawnShape(const FString& Name)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FRotator rotator = FRotator();

	rotator.Pitch = GetActorForwardVector().Y;

	FVector spawnLocation = GetActorLocation();

	spawnLocation = spawnLocation + (GetActorForwardVector() * ActorSpawnDist);

	spawnLocation.Z += 50.f;

	GetWorld()->SpawnActor<AHathorAiCharacterBase>(ShapeMap[Name], spawnLocation, rotator, spawnParams);
}

// Called when the game starts or when spawned
void AHathorChraracter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHathorChraracter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHathorChraracter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AHathorChraracter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHathorChraracter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void AHathorChraracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHathorChraracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHathorChraracter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHathorChraracter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &AHathorChraracter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpAtRate", this, &AHathorChraracter::LookUpAtRate);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

}

