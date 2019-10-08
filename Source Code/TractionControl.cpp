void drive(double fwd, double turn)
{
	
	double left = fwd - turn;
	double rght = fwd + turn; /* positive turn means turn robot LEFT */


	talLF.Set(ControlMode::PercentOutput, left);
	talLR.Set(ControlMode::PercentOutput, left);	
	talRF.Set(ControlMode::PercentOutput, rght*(-1));//reverse right side
	talRR.Set(ControlMode::PercentOutput, rght*(-1));

	double lfSpeed = talLF.getSpeed();
	double lrSpeed = talLR.getSpeed();
	double rfSpeed = talRF.getSpeed();
	double rrSpeed = talRF.getSpeed();
	
	//LEFT TRACTION CONTROL
	if (lfSpeed != lrSpeed) //Left back Talon not equal to Left front Talon
	{
		if(lfSpeed > lrSpeed) //Front faster than back
		{
			talLF.Set(ControlMode::PercentOutput, left); //Set to speed of left rear motor
			talLR.Set(ControlMode::PercentOutput, left);
		}

		else //Back faster than front
		{
			talLF.Set(ControlMode::PercentOutput, left);
			talLR.Set(ControlMode::PercentOutput, left); //Set to speed of left rear motor
		}	
	}

	else //Speed is equal
	{
		talLF.Set(ControlMode::PercentOutput, left);
		talLR.Set(ControlMode::PercentOutput, left);	
	}

	//RIGHT TRACTION CONTROL
	if (rfSpeed != rrSpeed) //Right back Talon not equal to Right front Talon
	{
		if(rfSpeed > rrSpeed) //Front faster than back
		{
			talLR.Set(ControlMode::PercentOutput, left); //Set to speed of right rear motor
			talLF.Set(ControlMode::PercentOutput, left);
		}

		else //Back faster than front
		{
			talRF.Set(ControlMode::PercentOutput, rght*(-1));
			talRR.Set(ControlMode::PercentOutput, rght*(-1)); //Set to speed of right rear motor
		}	
	}

	else //Speed is equal
	{
		talLF.Set(ControlMode::PercentOutput, left);
		talLR.Set(ControlMode::PercentOutput, left);	
	}

}
