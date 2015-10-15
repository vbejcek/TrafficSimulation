// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "LightSignal.h"


// Sets default values
ALightSignal::ALightSignal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	LightState = 0;

}

// Called when the game starts or when spawned
void ALightSignal::ToggleLight(){
	(LightState == 0) ? LightState = 1 : LightState = 0;
	UE_LOG(LogTemp, Warning, TEXT("ToggleLight"));
	return;
}

void ALightSignal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSignal::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

