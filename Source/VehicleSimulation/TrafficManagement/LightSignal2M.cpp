// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "LightSignal2M.h"


ALightSignal2M::ALightSignal2M() : ALightSignal()
{
	//UE_LOG(LogTemp, Warning, TEXT("Green"));

	
	
}

void ALightSignal2M::SetupMaterials(){
	UE_LOG(LogTemp, Warning, TEXT("SetupMat SignalLight 2?"));
	GreenLightMatInst = GetMaterialInstance(0);
	StaticMesh->SetMaterial(0, GreenLightMatInst);
	RedLightMatInst = GetMaterialInstance(3);
	StaticMesh->SetMaterial(3, RedLightMatInst);
}

void ALightSignal2M::SwitchState(){
	bool RedActive;
	if (LightState == 0){
		LightState = 1;
		RedActive = false;
	}
	else{
		LightState = 0;
		RedActive = true;
	}
	ActuateMaterial(GreenLightMatInst, !RedActive);
	ActuateMaterial(RedLightMatInst, RedActive);		
}

void ALightSignal2M::BeginPlay(){
	Super::BeginPlay();	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay LightSignal2M"));
	ActuateMaterial(RedLightMatInst, true);
}