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
    Timer autoTimer;
public:
	RobotDemo(void) :

		stick(1), driveLeft(2), driveRight(30), rollerLeft(9), rollerRight(11), 
		shootMotor(10), belt(13), bunnyDropFront(2), bunnyDropBack(1) 
		/*12-Open
		10-Side Ball Shooter
		9-Front Ball Roller
		13-Open
		30-Right Drive Cim
		2-Left Drive Cim
		8-Open
		*/
		
	{
		Watchdog().SetExpiration(1);
	}

	void Autonomous(void)
	{ 
		autoTimer.Start(); 
		while(true)
		{
			if(autoTimer.Get()>14)
			{
				bunnyDropFront.Set(1);
			}
			else
			{
				bunnyDropFront.Set(0);
			}
		}
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
			
			if(stick.GetRawButton(1))
			{
				driveLeft.Set(.1);
				driveRight.Set(-.1);
			}
			else if(stick.GetRawButton(2))
			{
				driveLeft.Set(.2);
				driveRight.Set(-.2);
			}
			else if(stick.GetRawButton(3))
			{
				driveLeft.Set(.3);
				driveRight.Set(-.3);
			}
			else if(stick.GetRawButton(4))
			{
				driveLeft.Set(.4);
				driveRight.Set(-.4);
			}
			else if(stick.GetRawButton(5))
			{
				driveLeft.Set(.5);
				driveRight.Set(-.5);
			}
			else if(stick.GetRawButton(6))
			{
				driveLeft.Set(.6);
				driveRight.Set(-.6);
			}
			else if(stick.GetRawButton(7))
			{
				driveLeft.Set(.7);
				driveRight.Set(-.7);
			}
			else if(stick.GetRawButton(8))
			{
				driveLeft.Set(.8);
				driveRight.Set(-.8);
			}
			else if(stick.GetRawButton(9))
			{
				driveLeft.Set(.9);
				driveRight.Set(-.9);
			}
			else if(stick.GetRawButton(10))
			{
				driveLeft.Set(1);
				driveRight.Set(-1);
			}
			else
			{
				driveLeft.Set(0);
				driveRight.Set(0);
			}
			
			
			
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

