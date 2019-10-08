#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <unistd.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

/* make some talons for drive train */
TalonSRX talL1(1);
TalonSRX talL2(2);
TalonSRX talR1(3);
TalonSRX talR2(4);

void drive(double fwd, double turn)
{
	double left = fwd - turn;
	double rght = fwd + turn; /* positive turn means turn robot LEFT */

	talL1.Set(ControlMode::PercentOutput, left);
	talL2.Set(ControlMode::PercentOutput, left);	
	talR2.Set(ControlMode::PercentOutput, left);
	talR1.Set(ControlMode::PercentOutput, left);

}

void motionMagic(double tal1, double tal2, double tal3, double tal4)
{
	double targetPos1 = 4096 * tal1; //Number of rotations to perform for Talon 1
	double targetPos2 = 4096 * tal2; //Number of rotations to perform for Talon 2
	double targetPos3 = 4096 * tal3; //Number of rotations to perform for Talon 3
	double targetPos4 = 4096 * tal4; //Number of rotations to perform for Talon 4

        talL1.Set(ControlMode::MotionMagic, targetPos1);
	talL2.Set(ControlMode::MotionMagic, targetPos2);
	talR1.Set(ControlMode::MotionMagic, targetPos3);
	talR2.Set(ControlMode::MotionMagic, targetPos4);

        /* Append more signals to print when in speed mode */
        sb << "\terr:" << _talon->GetClosedLoopError(0);
        sb << "\ttrg:" << targetPos;
}

/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {
	/* don't bother prompting, just use can0 */
	//std::cout << "Please input the name of your can interface: ";
	std::string interface;
	//std::cin >> interface;
	interface = "can0";
	ctre::phoenix::platform::can::SetCANInterface(interface.c_str());

	/* Set acceleration and vcruise velocity - see documentation */
	_talon->ConfigMotionCruiseVelocity(1500, 10);
	_talon->ConfigMotionAcceleration(1500, 10);

	//Add loop to perform MotionMagic for a period of time, then go to manual control
	motionMagic(10, 10, 10, 10);
	motionMagic(-10, -10, -10, -10);
	motionMagic(10, 10, 10, 10);

	drive(-.2,0);
	while(true){
	  ctre::phoenix::unmanaged::FeedEnable(100);
	  
	}     	
	return 0;
}
