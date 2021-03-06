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
		
	EmissiveCoefficientValue = 50.f;
	EmissiveCoefficientName = FName("EmissiveCoef");
	LightState = 0;
	

}

UMaterialInstanceDynamic* ALightSignal::GetMaterialInstance(int32 i){
	//static UMaterialInstanceDynamic return new material based on given parent.
	return UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(i), this);
}

// Intended to be called from SignalMannager
void ALightSignal::OnToggleEvent(float TimeToTransition){
	TransitionDelay = TimeToTransition;
	SetTransitionDelayTimer();
}

void ALightSignal::SetTransitionDelayTimer(){
	GetWorld()->GetTimerManager().SetTimer(TransitionDelayTimer, this, &ALightSignal::OnTimerFireEvent, TransitionDelay, false);
}

void ALightSignal::OnTimerFireEvent(){
	GetWorld()->GetTimerManager().ClearTimer(TransitionDelayTimer);
	SwitchState();
}


void ALightSignal::ActuateMaterial(UMaterialInstanceDynamic* mat, bool illuminate){
	float Val;
	(illuminate) ? Val = EmissiveCoefficientValue : Val = 0;
	mat->SetScalarParameterValue(EmissiveCoefficientName, Val);
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

void ALightSignal::SetupMaterials(){
	//implemented in subclasses
}

void ALightSignal::SwitchState(){
	//implemented in subclasses
}

