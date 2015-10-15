// Vít Bejček - 2015 - VehicleSimulation

#include "VehicleSimulation.h"
#include "RearWheel.h"


URearWheel::URearWheel(){
	bAffectedByHandbrake = true;
	SteerAngle = 0.0f;
	ShapeRadius = 35.0f;
	ShapeWidth = 10.0f;
}