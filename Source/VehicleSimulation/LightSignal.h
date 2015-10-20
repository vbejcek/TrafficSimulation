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

	UMaterialInstanceDynamic* RedLightMatInst;

	UMaterialInstanceDynamic* GreenLightMatInst;
	
	int32 LightState;

	FTimerHandle SignalTimer;

	UMaterialInstanceDynamic* GetMaterialInstance(int32 i);

	void ToggleSignalLight();

	void SwitchState();

	void SetupMaterials();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
