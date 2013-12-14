#include "WPILib.h"

class RobotDemo : public SimpleRobot {
	Joystick stick;
	CANJaguar driveLeft;
	CANJaguar driveRight;
	CANJaguar rollerLeft;
	CANJaguar rollerRight;
	CANJaguar shootMotor;
	CANJaguar belt;
	Servo bunnyDropFront;
    Servo bunnyDropBack;
public:
	RobotDemo(void) :

		stick(1), driveLeft(2), driveRight(30), rollerLeft(9), rollerRight(11), 
		shootMotor(10), belt(13), bunnyDropFront(2), bunnyDropBack(1) 
	{
		Watchdog().SetExpiration(1);
	}

	void Autonomous(void)
	{

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) 
	{
		DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		Watchdog().SetEnabled(true);
		bool button6Pressed = false;
		bool button8Pressed = false;
		float shooterSpeed = 0.0;
		
		while (IsOperatorControl()) 
		{
			Watchdog().Feed();
			
			driveLeft.Set(stick.GetRawAxis(2));
			driveRight.Set(stick.GetRawAxis(4));
			
			//printf("Speed: %f\n", speed);
			//printf("Voltage: %f\n", voltage);
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "I'm running!");
			 dsLCD->UpdateLCD();
			
			if (stick.GetRawButton(3))
			{
				bunnyDropFront.Set(1);
				bunnyDropBack.Set(1);
			}
			if (stick.GetRawButton(4))
			{
				bunnyDropFront.Set(0);
				bunnyDropBack.Set(0);
			}
			if (stick.GetRawButton(5)) 
			{
				rollerLeft.Set(1);
				rollerRight.Set(1);
			} 
			else 
			{
				rollerLeft.Set(0);
				rollerRight.Set(0);
			}
			if (stick.GetRawButton(6) && shooterSpeed < 1 && button6Pressed
					== false) 
			{
				shooterSpeed += .1;
				button6Pressed = true;
			} 
			else if (stick.GetRawButton(6)==false) 
			{
				button6Pressed = false;
			}
			if (stick.GetRawButton(8) && shooterSpeed> 0 && button8Pressed
					== false) 
			{
				shooterSpeed -= .1;
				button8Pressed = true;
			} 
			else if (stick.GetRawButton(8)==false) 
			{
				button8Pressed = false;
			}
			if (stick.GetRawButton(1)) 
			{
				shooterSpeed = 1;
			}
			if (stick.GetRawButton(2)) 
			{
				shooterSpeed = 0;
			}
			shootMotor.Set(shooterSpeed);
			if (stick.GetRawButton(7)) 
			{
				belt.Set(1);
			} 
			else 
			{
				belt.Set(0);}
			}
		}

	/**
	 * Runs during test mode
	 */
	void Test() 
	{

	}
};

START_ROBOT_CLASS(RobotDemo)
;

