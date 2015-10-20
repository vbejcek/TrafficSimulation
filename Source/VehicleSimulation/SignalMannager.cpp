// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "SignalMannager.h"
#include "LightSignal.h"


// Sets default values
ASignalMannager::ASignalMannager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MannagerSprite = CreateDefaultSubobject<UBillboardComponent>(TEXT("MannagerSprite"));
	MannagerSprite->AttachTo(RootComponent);
	SignalInterval = 5.0f; //in seconds
	

}

void ASignalMannager::OnTimerFire(){
	UE_LOG(LogTemp, Warning, TEXT("TimerFire"));
	if (GroupA.Num() > 0){
		for (uint8 i = 0; i < GroupA.Num(); i++){
			GroupA[i]->ToggleSignalLight();
		}
	}
}

// Called when the game starts or when spawned
void ASignalMannager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()){
		GetWorld()->GetTimerManager().SetTimer(SignalTimer, this, &ASignalMannager::OnTimerFire, SignalInterval, true);
	}
	
}

// Called every frame
void ASignalMannager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	

}

