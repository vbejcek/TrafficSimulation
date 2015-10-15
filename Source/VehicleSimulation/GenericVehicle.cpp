//Vít Bejèek - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GenericVehicle.h"
#include "Engine.h"
#include "FrontWheel.h"
#include "RearWheel.h"


AGenericVehicle::AGenericVehicle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	
	//Note - While more than one pawn is spawned in world error occurs
	LookUpBinding = FName(TEXT("LookUp"));
	LookRightBinding = FName(TEXT("LookRight"));
	bHandbrakeOn = false;
	bReverseOn = false;
	
	//SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(RootComponent);
	SpringArm->AddRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
	SpringArm->AddRelativeRotation(FRotator(-25.0f, 0.f, 0.f));
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	//InnerCamera
	InnerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InnerCamera"));
	InnerCamera->AttachTo(GetMesh());
	InnerCamera->AddRelativeLocation(FVector(0.0f, -40.0f, 125.0f));
	InnerCamera->bUsePawnControlRotation = false;
	InnerCamera->Activate();	
	
	//OuterCamera
	OuterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OuterCamera"));
	OuterCamera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	//Ligts
		//LeftHeadlight
	LeftHeadlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftHeadlight"));
	LeftHeadlight->SetRelativeLocation(FVector(220.0f, -65.0f, 80.0f));
	SetupVehicleLight(LeftHeadlight, 50000.f, 3000.f, true);
	LeftHeadlight->OuterConeAngle = 50.f;
		//RightHeadlight
	RightHeadlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightHeadlight"));
	RightHeadlight->SetRelativeLocation(FVector(220.0f, 65.0f, 80.0f));
	SetupVehicleLight(RightHeadlight, 50000.f, 3000.f, true);
	RightHeadlight->OuterConeAngle = 50.f;
		//LeftBreaklight
	LeftBreaklight = CreateDefaultSubobject<USpotLightComponent>(TEXT("LeftBreaklight"));
	LeftBreaklight->SetRelativeLocation(FVector(-215.0f, -65.0f, 110.0f));
	LeftBreaklight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	LeftBreaklight->SetLightColor(FLinearColor(255.f, 0.f, 0.f, 1.f));
	SetupVehicleLight(LeftBreaklight, 50000.f, 3000.f, false);
	LeftBreaklight->OuterConeAngle = 80.f;
		//RightBreaklight
	RightBreaklight = CreateDefaultSubobject<USpotLightComponent>(TEXT("RightBreaklight"));
	RightBreaklight->SetRelativeLocation(FVector(-215.0f, 65.0f, 110.0f));
	RightBreaklight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	RightBreaklight->SetLightColor(FLinearColor(255.f, 0.f, 0.f, 1.f));
	SetupVehicleLight(RightBreaklight, 50000.f, 3000.f, false);
	RightBreaklight->OuterConeAngle = 80.f;
		//LeftFrontDirectionalLight
	LFDirectionalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LFDirectionalLight"));
	LFDirectionalLight->SetRelativeLocation(FVector(216.0f, -80.0f, 80.0f));
	LFDirectionalLight->SetLightColor(FLinearColor(200.f, 100.f, 0.f));
	SetupVehicleLight(LFDirectionalLight, 15000.f, 500.f, false);
		//RightFrontDirectionalLight
	RFDirectionalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RFDirectionalLight"));
	RFDirectionalLight->AttachTo(GetMesh());
	RFDirectionalLight->SetRelativeLocation(FVector(216.0f, 80.0f, 80.0f));
	RFDirectionalLight->SetLightColor(FLinearColor(200.f, 100.f, 0.f));
	SetupVehicleLight(RFDirectionalLight, 15000.f, 500.f, false);
		//LeftRearDirectionalLight
	LRDirectionalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LRDirectionalLight"));
	LRDirectionalLight->AttachTo(GetMesh());
	LRDirectionalLight->SetRelativeLocation(FVector(-215.0f, -75.0f, 110.0f));
	LRDirectionalLight->SetLightColor(FLinearColor(200.f, 100.f, 0.f));
	SetupVehicleLight(LRDirectionalLight, 15000.f, 500.f, false);
		//RightRearDirectionalLight
	RRDirectionalLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("RRDirectionalLight"));
	RRDirectionalLight->AttachTo(GetMesh());
	RRDirectionalLight->SetRelativeLocation(FVector(-215.0f, 75.0f, 110.0f));
	RRDirectionalLight->SetLightColor(FLinearColor(200.f, 100.f, 0.f));
	SetupVehicleLight(RRDirectionalLight, 15000.f, 500.f, false);


	//Wheels
	UWheeledVehicleMovementComponent4W* Vehicle4w = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());
	
		//FrontLeft
	Vehicle4w->WheelSetups[0].WheelClass = UFrontWheel::StaticClass();
	Vehicle4w->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	Vehicle4w->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

		//FrontRight
	Vehicle4w->WheelSetups[1].WheelClass = UFrontWheel::StaticClass();
	Vehicle4w->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	Vehicle4w->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);
		//RearLeft
	Vehicle4w->WheelSetups[2].WheelClass = URearWheel::StaticClass();
	Vehicle4w->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	Vehicle4w->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);
		//RearRight
	Vehicle4w->WheelSetups[3].WheelClass = URearWheel::StaticClass();
	Vehicle4w->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	Vehicle4w->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

}

void AGenericVehicle::MoveForward(float val){
	(val < 0) ? bReverseOn = true : bReverseOn = false;
	
	GetVehicleMovementComponent()->SetThrottleInput(val);
}

void AGenericVehicle::MoveRight(float val){
	GetVehicleMovementComponent()->SetSteeringInput(val);
	}

void AGenericVehicle::LookRight(float val){

}

void AGenericVehicle::ApplyHandbrake(){
	bHandbrakeOn = true;
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	}

void AGenericVehicle::ReleaseHandbrake(){
	bHandbrakeOn = false;
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AGenericVehicle::ChangeCamera(){
	if (InnerCamera->IsActive()){
		InnerCamera->Deactivate();
		OuterCamera->Activate();		
	}
	else{
		OuterCamera->Deactivate();
		InnerCamera->Activate();
		
	}
}

void AGenericVehicle::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	InputComponent->BindAxis("MoveForward", this, &AGenericVehicle::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGenericVehicle::MoveRight);
	
	InputComponent->BindAxis(LookRightBinding);
	InputComponent->BindAxis(LookUpBinding);

	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &AGenericVehicle::ChangeCamera);
	InputComponent->BindAction("ToggleHeadlights", IE_Pressed, this, &AGenericVehicle::ToggleHeadlights);

	InputComponent->BindAction("LeftDirectionalLights", IE_Pressed, this, &AGenericVehicle::ToggleLeftDirectionalLights);
	InputComponent->BindAction("RightDirectionalLights", IE_Pressed, this, &AGenericVehicle::ToggleRightDirectionalLights);
	InputComponent->BindAction("ToggleEmergencyWarning", IE_Pressed, this, &AGenericVehicle::ToggleEmergencyWarning);

	InputComponent->BindAction("Handbrake", IE_Pressed, this, &AGenericVehicle::ApplyHandbrake);
	InputComponent->BindAction("Handbrake", IE_Released, this, &AGenericVehicle::ReleaseHandbrake);
}

void AGenericVehicle::Tick(float DeltaSeconds){
	if (InnerCamera->IsActive() && InputComponent){
		FRotator HeadRotation = InnerCamera->RelativeRotation;
		HeadRotation.Pitch += InputComponent->GetAxisValue(LookUpBinding);
		HeadRotation.Yaw += InputComponent->GetAxisValue(LookRightBinding);
		InnerCamera->RelativeRotation = HeadRotation;
	}
	else if(InputComponent){
		FRotator ArmRotation = SpringArm->RelativeRotation;
		ArmRotation.Pitch += InputComponent->GetAxisValue(LookUpBinding);
		ArmRotation.Yaw += InputComponent->GetAxisValue(LookRightBinding);
		SpringArm->RelativeRotation = ArmRotation;

	}
	SetBreaklights();
}

void AGenericVehicle::ToggleHeadlights(){
	LeftHeadlight->ToggleVisibility();
	RightHeadlight->ToggleVisibility();
}

void AGenericVehicle::SetBreaklights(){
	if (bHandbrakeOn || bReverseOn){
		LeftBreaklight->SetVisibility(true);
		RightBreaklight->SetVisibility(true);
	}
	else{
		LeftBreaklight->SetVisibility(false);
		RightBreaklight->SetVisibility(false);
	}
}

void AGenericVehicle::ToggleLeftDirectionalLights(){
	bEmergencyWarningOn = false;
	bLeftDirectionalLightsOn = !bLeftDirectionalLightsOn;
	bRightDirectionalLightsOn = false;	
	SetDirectionalLights(bLeftDirectionalLightsOn, bRightDirectionalLightsOn);
}

void AGenericVehicle::ToggleRightDirectionalLights(){
	bEmergencyWarningOn = false;
	bLeftDirectionalLightsOn = false;
	bRightDirectionalLightsOn = !bRightDirectionalLightsOn;
	SetDirectionalLights(bLeftDirectionalLightsOn, bRightDirectionalLightsOn);
}

void AGenericVehicle::ToggleEmergencyWarning(){
	bLeftDirectionalLightsOn = false;
	bRightDirectionalLightsOn = false;
	bEmergencyWarningOn = !bEmergencyWarningOn;
	SetDirectionalLights(bEmergencyWarningOn, bEmergencyWarningOn);
}

void AGenericVehicle::SetDirectionalLights(bool left, bool right){
	LFDirectionalLight->SetVisibility(left);
	RFDirectionalLight->SetVisibility(right);
	LRDirectionalLight->SetVisibility(left);
	RRDirectionalLight->SetVisibility(right);
}

void AGenericVehicle::SetupVehicleLight(UPointLightComponent* light, float intensity, float radius, bool bVisibility){
	light->AttachTo(GetMesh());
	light->bUseInverseSquaredFalloff = true;
	light->LightFalloffExponent = 4.f;
	light->Intensity = intensity;//in lumens for InverseSquareFalloff
	light->AttenuationRadius = radius;
	light->SetVisibility(bVisibility);
}