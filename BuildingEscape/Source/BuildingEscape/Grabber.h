// Copywrite Sloan Stewart 2018

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	/// Ray-cast and Grab what is within Reach
	void Grab();
	
	/// Called when grab is released
	void Release();

	/// Find attached PhysicsHandle
	void FindPhysicsHandleComponent();

	/// Setup attachdd InputComponent
	void SetupInputComponent();

	/// Return Hit for first PhysicsBody in Reach
	const FHitResult GetFirstPhysicsBodyInReach();

	/// Returns current start of Reach line
	FVector GetReachLineStart();

	/// Returns current end of Reach line
	FVector GetReachLineEnd();
};
