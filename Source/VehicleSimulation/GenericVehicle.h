// Vít Bejèek - 2015 - VehicleSimulation

#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "GenericVehicle.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;

UCLASS()
class VEHICLESIMULATION_API AGenericVehicle : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	UCameraComponent* InnerCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* OuterCamera;

	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = Lights)
	USpotLightComponent* LeftHeadlight;

	UPROPERTY(EditAnywhere, Category = Lights)
	USpotLightComponent* RightHeadlight;

	UPROPERTY(EditAnywhere, Category = Lights)
	USpotLightComponent* RightBreaklight;

	UPROPERTY(EditAnywhere, Category = Lights)
	USpotLightComponent* LeftBreaklight;

	UPROPERTY(EditAnywhere, Category = Lights)
	UPointLightComponent* LFDirectionalLight;

	UPROPERTY(EditAnywhere, Category = Lights)
	UPointLightComponent* RFDirectionalLight;

	UPROPERTY(EditAnywhere, Category = Lights)
	UPointLightComponent* LRDirectionalLight;

	UPROPERTY(EditAnywhere, Category = Lights)
	UPointLightComponent* RRDirectionalLight;

	UPROPERTY(EditAnywhere, Category = Lights)
	bool bLeftDirectionalLightsOn;

	UPROPERTY(EditAnywhere, Category = Lights)
	bool bRightDirectionalLightsOn;

	UPROPERTY(EditAnywhere, Category = Lights)
	bool bEmergencyWarningOn;

	FName LookUpBinding;
	FName LookRightBinding;
	

protected:
	void MoveForward(float val);

	void MoveRight(float val);

	void LookRight(float val);

	void LookUp(float val);

	void ApplyHandbrake();

	void ReleaseHandbrake();

	void ChangeCamera();

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Tick(float DeltaSeconds) override;

	void ToggleHeadlights();

	void SetBreaklights();

	void ToggleLeftDirectionalLights();

	void ToggleRightDirectionalLights();

	void SetDirectionalLights(bool left, bool right);

	void ToggleEmergencyWarning();

	void SetupVehicleLight(UPointLightComponent* light, float intensity, float radius, bool bVisibility);

	bool bHandbrakeOn;
	bool bReverseOn;
	
	
};
  