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

	UPROPERTY(EditDefaultsOnly, Category = Signals)
	TArray<ALightSignal*> GroupA;
	
	UPROPERTY(EditDefaultsOnly, Category = Signals)
	float SignalInterval;

	FTimerHandle SignalTimer;

	void OnTimerExpiration();
};
