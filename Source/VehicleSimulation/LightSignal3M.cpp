// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "LightSignal3M.h"


ALightSignal3M::ALightSignal3M() : ALightSignal()
{
	

}

void ALightSignal3M::OnToggleEvent(float TimeToTransition){
	TransitionDelay = TimeToTransition / 2; // There are 2 states in transition
	SetTransitionDelayTimer();
}

// 0 - Red; 1 - Red + Amber; 2 Green; 3 - Amber
void ALightSignal3M::SwitchState(){
	switch(LightState){
		case 0:
			ActuateMaterial(RedLightMatInst, true);
			ActuateMaterial(AmberLightMatInst, true);
			ActuateMaterial(GreenLightMatInst, false);
			LightState = 1;
			SetTransitionDelayTimer();
			break;
		case 1:
			ActuateMaterial(RedLightMatInst, false);
			ActuateMaterial(AmberLightMatInst, false);
			ActuateMaterial(GreenLightMatInst, true);
			LightState = 2;
			break;
		case 2:
			ActuateMaterial(RedLightMatInst, false);
			ActuateMaterial(AmberLightMatInst, true);
			ActuateMaterial(GreenLightMatInst, false);
			LightState = 3;
			SetTransitionDelayTimer();
			break;
		case 3:
			ActuateMaterial(RedLightMatInst, true);
			ActuateMaterial(AmberLightMatInst, false);
			ActuateMaterial(GreenLightMatInst, false);
			LightState = 0;
			break;
	}
}

void ALightSignal3M::SetupMaterials(){
	GreenLightMatInst = GetMaterialInstance(0);
	StaticMesh->SetMaterial(0, GreenLightMatInst);
	AmberLightMatInst = GetMaterialInstance(3);
	StaticMesh->SetMaterial(3, AmberLightMatInst);
	RedLightMatInst = GetMaterialInstance(4);
	StaticMesh->SetMaterial(4, RedLightMatInst);
}

void ALightSignal3M::BeginPlay(){
	Super::BeginPlay();

	ActuateMaterial(RedLightMatInst, true);
}

