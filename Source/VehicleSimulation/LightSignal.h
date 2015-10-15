// Vít Bejček - 2015 - VehicleSimulation

#pragma once

#include "GameFramework/Actor.h"
#include "LightSignal.generated.h"

UCLASS()
class VEHICLESIMULATION_API ALightSignal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSignal();

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	uint8 LightState;

	void ToggleLight();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
