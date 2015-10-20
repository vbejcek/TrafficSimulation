// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "LightSignal.h"


// Sets default values
ALightSignal::ALightSignal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->AttachTo(RootComponent);
	
	LightState = 0; // 0 - red, 1 - green

}

UMaterialInstanceDynamic* ALightSignal::GetMaterialInstance(int32 i){
	//static UMaterialInstanceDynamic return new material based on given parent.
	return UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(i), this);
}

// Intended to be called from SignalMannager
void ALightSignal::ToggleSignalLight(){
	GetWorld()->GetTimerManager().SetTimer(SignalTimer, this, &ALightSignal::SwitchState, 1.0f, false);
	UE_LOG(LogTemp, Warning, TEXT("ToggleLight"));
}

// Invoked on SignalTimer fire event
void ALightSignal::SwitchState(){
	if (LightState == 0){
		LightState = 1;
		RedLightMatInst->SetScalarParameterValue(FName("EmissiveCoef"), 0.f);
		GreenLightMatInst->SetScalarParameterValue(FName("EmissiveCoef"), 50.f);
		UE_LOG(LogTemp, Warning, TEXT("Green"));
	}
	else{
		LightState = 0;
		GreenLightMatInst->SetScalarParameterValue(FName("EmissiveCoef"), 0.f);
		RedLightMatInst->SetScalarParameterValue(FName("EmissiveCoef"), 50.f);
		UE_LOG(LogTemp, Warning, TEXT("Red"));
	}
	GetWorld()->GetTimerManager().ClearTimer(SignalTimer);
}

// Called after BeginPlay() to setup instantiante and se SignalLight materials
void ALightSignal::SetupMaterials(){

	GreenLightMatInst = GetMaterialInstance(0);
	StaticMesh->SetMaterial(0, GreenLightMatInst);
	RedLightMatInst = GetMaterialInstance(3);
	StaticMesh->SetMaterial(3, RedLightMatInst);

}

// Called when the game starts or when spawned
void ALightSignal::BeginPlay()
{
	Super::BeginPlay();

	SetupMaterials();
}

// Called every frame
void ALightSignal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

