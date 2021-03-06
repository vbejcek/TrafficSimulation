// Vít Bejček - 2015 - VehicleSimulation

#pragma once

#include "LightSignal.h"
#include "LightSignal3M.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESIMULATION_API ALightSignal3M : public ALightSignal
{
	GENERATED_BODY()

		ALightSignal3M();

public:
	virtual void OnToggleEvent(float TimeToTransition);

	UMaterialInstanceDynamic* AmberLightMatInst;
	void SwitchState() override;
	void SetupMaterials()override;
	void BeginPlay() override;
	
};
