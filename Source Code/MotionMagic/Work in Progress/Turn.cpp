// Global variables
double trackWidth = 24.0;
double wheelRadius = 4.0;


public turn(String inDirection, double inDegree) //Pass in direction and degree of the turn
{
	String direction = inDirection; //May need strcopy
	double degree = inDegree;
	double rotations = (degree * trackWidth) / (2 * 360 * wheelRadius); //trackWidth and wheelRadius should be global variables

	double leftRotations = 0; //Initialize
	double rightRotations = 0;
	
	if (direction == "left") //May need .equals()
	{
		//left motors turn forward, right turn backward
		leftRotations = rotations
		rightRotations = -rotations
	}
	else if (direction == "right") //May need .equals()
	{
		//right motors turn forward, left turn backward
		rightRotations = rotations
		leftRotations = -rotations
	}

	double rightPos = 4096 * rightRotations; //4096 ticks per rev
	double leftPos = 4096 * leftRotations; //4096 ticks per rev
	
        frontRight->Set(ControlMode::MotionMagic, rightPos);
        backRight->Set(ControlMode::MotionMagic, rightPos);
        frontLeft->Set(ControlMode::MotionMagic, leftPos);
        backLeft->Set(ControlMode::MotionMagic, leftPos);
}

//This function will estimate the rotations required for a specific turn and will perform the turn
//The camera will then be used to make any needed positional corrections
