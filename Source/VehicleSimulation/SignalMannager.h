// Vít Bejček - 2015 - VehicleSimulation

#pragma once

#include "GameFramework/Actor.h"
#include "SignalMannager.generated.h"

class ALightSignal;

UCLASS()
class VEHICLESIMULATION_API ASignalMannager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignalMannager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = Sprite)
	UBillboardComponent* MannagerSprite;

	UPROPERTY(EditAnywhere, Category = Signals)
	TArray<ALightSignal*> GroupA;

	UPROPERTY(EditAnywhere, Category = Signals)
	TArray<ALightSignal*> GroupB;
	
	UPROPERTY(EditAnywhere, Category = Timers)
	float SignalInterval;

	UPROPERTY(EditAnywhere, Category = Timers)
	float ToggleTime;

	FTimerHandle SignalTimer;
	FTimerHandle DelayedTimer;

	bool ActiveGroupA;
	bool ActiveGroupB;

	/*UPROPERTY(EditAnywhere, Category = Signals)
	TArray<TArray<ALightSignal*>> VectorGroup;*/

	void OnDelayedTimerFire();

	

	void OnTrafficTimerFire();

	void ToggleTrafficGroup(TArray<ALightSignal*>);
};
