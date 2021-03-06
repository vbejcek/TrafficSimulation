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
	SignalInterval = 8.0f; //in seconds
	ToggleTime = 3.0f;
	ActiveGroupA = false;
	ActiveGroupB = false;
	

}
// Determines which group is turned on and turns it off, sets delay for another group to be turned on.
void ASignalMannager::OnTrafficTimerFire(){
	if (ActiveGroupA){
		ToggleTrafficGroup(GroupA);
	}
	else
	{
		ToggleTrafficGroup(GroupB);
	}
	GetWorld()->GetTimerManager().SetTimer(DelayedTimer, this, &ASignalMannager::OnDelayedTimerFire, ToggleTime, false);
}

// At this point both Groups should be turned off
void ASignalMannager::OnDelayedTimerFire(){
	if (!ActiveGroupA){
		ToggleTrafficGroup(GroupA);
	}
	else
	{
		ToggleTrafficGroup(GroupB);
	}
}

// Toggles all ALightSignal object assigned to this group
void ASignalMannager::ToggleTrafficGroup(TArray<ALightSignal*> g){
	(g == GroupA) ? ActiveGroupA != ActiveGroupA : ActiveGroupB != ActiveGroupB;
	if (g == GroupA){
		UE_LOG(LogTemp, Warning, TEXT("is g A"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("is g B"));
	}
	if (g.Num() > 0){
		for (int32 i = 0; i < g.Num(); i++){
			g[i]->OnToggleEvent(ToggleTime);
		}
	}
}

// Called when the game starts or when spawned
void ASignalMannager::BeginPlay()
{
	Super::BeginPlay();

	ToggleTrafficGroup(GroupA);

	if (GetWorld()){
		GetWorld()->GetTimerManager().SetTimer(SignalTimer, this, &ASignalMannager::OnTrafficTimerFire, SignalInterval, true);
	}
	
}

// Called every frame
void ASignalMannager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	

}

