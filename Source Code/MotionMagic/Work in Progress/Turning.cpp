double trackWidth = 24.0;
double wheelRadius = 4.0;
double degreeOfTurn = 90.0;
String direction = "left";
double pointRotations = (degreeOfTurn * trackWidth) / (2 * 360 * wheelRadius);
double pivotRotations = (degreeOfTurn * trackWidth) / (2 * 2 * 360 * wheelRadius);
if () //pivot turn
{
	if (direction == "left")
	{
		//left motors turn only
		//leftRotations = pointRotations
		//rightRotations = 0
	}
	else if (direction == "right")
	{
		//right motors turn only
		//rightRotations = pointRotations
		//leftRotations = 0
	}
}
else if () //point turn
{
	if (direction == "left")
	{
		//left motors turn forward, right turn backward
		//leftRotations = pointRotations
		//rightRotations = -pointRotations
	}
	else if (direction == "right")
	{
		//right motors turn forward, left turn backward
		//rightRotations = pointRotations
		//leftRotations = -pointRotations
	}
}
