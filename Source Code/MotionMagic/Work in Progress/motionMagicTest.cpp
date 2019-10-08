#include <iostream>
using namespace std;

int main ()
{
	/*Initialize*/

	frontLeft = new TalonSRX(1);
	frontRight = new TalonSRX(2);
	backLeft = new TalonSRX(3);
	backRight = new TalonSRX(4);

	/* Make sure lights are green when driving forward */
	frontLeft->SetInverted(false);
	frontRight->SetInverted(false);
	backLeft->SetInverted(false);
	backRight->SetInverted(false);

	/* Set acceleration and vcruise velocity */
    	frontLeft->ConfigMotionCruiseVelocity(1500, 10);
    	frontLeft->ConfigMotionAcceleration(1500, 10);
    	
    	frontRight->ConfigMotionCruiseVelocity(1500, 10);
    	frontRight->ConfigMotionAcceleration(1500, 10);
    	
    	backLeft->ConfigMotionCruiseVelocity(1500, 10);
    	backLeft->ConfigMotionAcceleration(1500, 10);
    	
    	backRight->ConfigMotionCruiseVelocity(1500, 10);
    	backRight->ConfigMotionAcceleration(1500, 10);

    	/* Zero the sensor */
    	_talon->SetSelectedSensorPosition(0, 0, 10);

	double flPos;
	double frPos;
	double blPos;
	double brPos;

	int size = 3; /*set number of positions*/
	
	/*array of positions to follow*/
	double fl[3] = {10.0, 20.0, 30.0};
	double fr[3] = {10.0, 20.0, 30.0};
	double bl[3] = {10.0, 20.0, 30.0};
	double br[3] = {10.0, 20.0, 30.0};

	int i = 0;
	while(i < size)
	{
		flPos = fl[i];
		frPos = fr[i];
		blPos = bl[i];
		brPos = br[i];

		frontLeft->Set(ControlMode::MotionMagic, flPos);
		frontRight->Set(ControlMode::MotionMagic, frPos);
		backLeft->Set(ControlMode::MotionMagic, blPos);
		backRight->Set(ControlMode::MotionMagic, brPos);
		i = i + 1;
	}

	/*Follow points in Reverse order*/

	int i = size - 1;
	while(i > -1)
	{
		flPos = - fl[i];
		frPos = - fr[i];
		blPos = - bl[i];
		brPos = - br[i];
	
		frontLeft->Set(ControlMode::MotionMagic, flPos);
		frontRight->Set(ControlMode::MotionMagic, frPos);
		backLeft->Set(ControlMode::MotionMagic, blPos);
		backRight->Set(ControlMode::MotionMagic, brPos);
		i = i - 1;
	}

	/*This should lead back to starting point*/
	
	
}
