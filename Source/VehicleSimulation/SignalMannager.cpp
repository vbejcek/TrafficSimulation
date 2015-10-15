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
	SignalInterval = 10.f;


}

void ASignalMannager::OnTimerExpiration(){
	GetWorld()->GetTimerManager().SetTimer(&OnTimerExpiration, SignalTimer);
}

// Called when the game starts or when spawned
void ASignalMannager::BeginPlay()
{
	Super::BeginPlay();	
	
}

// Called every frame
void ASignalMannager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GroupA.Num() > 0){
		for (uint8 i = 0; i < GroupA.Num(); i++){
			GroupA[i]->ToggleLight();
		}
	}

}

