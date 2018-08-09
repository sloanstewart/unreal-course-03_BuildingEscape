// Copywrite Sloan Stewart 2018

#include "OpenDoor.h"
#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate not found in %s"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor()
{
	// Set door rotation
	// Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	// Set door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the Trigger volume
	if (GetTotalMassOfActorsOnPlate() > 30.f) /// TODO: make param
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	// Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	/// Find all overlapping actors
	TArray<AActor *> OverlappingActors;
	if (!PressurePlate)
	{
		return TotalMass;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	/// Iterate through them adding their mass
	for (const auto *Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}