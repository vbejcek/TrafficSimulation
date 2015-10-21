// Vít Bejček - 2015 - VehicleSimulation

#pragma once

#include "LightSignal.h"
#include "LightSignal2M.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLESIMULATION_API ALightSignal2M : public ALightSignal
{
	GENERATED_BODY()

		ALightSignal2M();
	
	void SetupMaterials() override;

	void SwitchState() override;

	virtual void BeginPlay() override;
	
	
	
};
