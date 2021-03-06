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
	
	// Which light is currently on - state
	int32 LightState;

	float EmissiveCoefficientValue;

	// Parametr name of material
	FName EmissiveCoefficientName;

	// Timer which is instantiated each transition. Destroyed in SwitchState()

	UMaterialInstanceDynamic* GetMaterialInstance(int32 i);

	FTimerHandle TransitionDelayTimer;

	float TransitionDelay;

	// Intended to be called from SignalMannager
	virtual void OnToggleEvent(float TimeToTransition);

	virtual void SetTransitionDelayTimer();

	virtual void OnTimerFireEvent();

	// Invoked on SignalTimer fire event
	virtual void SwitchState();

	// Called after BeginPlay() to setup instantiante and se SignalLight materials
	virtual void SetupMaterials();

	void ActuateMaterial(UMaterialInstanceDynamic* mat, bool illuminate);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	// Handles SignalTimer fire event - consequently clears timer and pass call chain to SwtichState()
	void OnSignalTimerFire();

	
	
};
