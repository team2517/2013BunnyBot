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
		shootMotor(10), belt(12), bunnyDropFront(2), bunnyDropBack(1) 
		/*12- Track Banebot
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
		while(autoTimer.Get() < 11)
		{
			bunnyDropFront.Set(1);
			bunnyDropBack.Set(0);
			
			if(autoTimer.Get() < 6.5)
			{	//Turned left at .53 -.5
				//right at .6 -.5
				driveLeft.Set(.57);
				driveRight.Set(-.5);
			}
			else
			{
				driveLeft.Set(0);
				driveRight.Set(0);
			}
		}
		
		bunnyDropFront.Set(0);
		bunnyDropBack.Set(1);
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
		bool button3Pressed = false;
		bool button4Pressed = false;
		float shooterSpeed = 0.0;
		float stickMotorRatio = 1.0;
		
		
		while (IsOperatorControl()) 
		{
			Watchdog().Feed();
			
			
			//printf("Speed: %f\n", speed);
			//printf("Voltage: %f\n", voltage);
			
			/*
			if (stick.GetRawButton(3))
			{
				bunnyDropFront.Set(1);
				bunnyDropBack.Set(1);
				dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Button Pressed");
				
			}
			if (stick.GetRawButton(4))
			{
				bunnyDropFront.Set(0);
				bunnyDropBack.Set(0);
				dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "");

			}*/
			if (stick.GetRawButton(5)) 
			{
				rollerLeft.Set(1);
				rollerRight.Set(-1);
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
			if (stick.GetRawButton(8) && shooterSpeed > 0 && button8Pressed
					== false) 
			{
				shooterSpeed -= .1;
				button8Pressed = true;
			} 
			else if (stick.GetRawButton(8) == false)
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
			
			if (stick.GetRawButton(4) && stickMotorRatio < 1 && button4Pressed
					== false) 
			{
				stickMotorRatio += .05;
				button4Pressed = true;
			} 
			else if (stick.GetRawButton(4)==false) 
			{
				button4Pressed = false;
			}
			if (stick.GetRawButton(3) && stickMotorRatio > 0 && button3Pressed
					== false) 
			{
				stickMotorRatio -= .05;
				button3Pressed = true;
			} 
			else if (stick.GetRawButton(3)==false) 
			{
				button3Pressed = false;
			}
			
			if (stick.GetRawButton(7)) 
			{
				belt.Set(-.5);
			} 
			else 
			{
				belt.Set(0);
			}
			
			if(stick.GetRawAxis(2) > .05 || stick.GetRawAxis(2) < -.05)
			{
				driveLeft.Set(stickMotorRatio * -stick.GetRawAxis(2));
			}
			else
			{
				driveLeft.Set(0);
			}
			if(stick.GetRawAxis(4) > .05 || stick.GetRawAxis(4) < -.05)
			{
				driveRight.Set(stickMotorRatio * stick.GetRawAxis(4));
			}
			else
			{
				driveRight.Set(0);
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "shooter = %f", shooterSpeed);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, 
					"stickMotorRatio = %f", stickMotorRatio);
			dsLCD->UpdateLCD();
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

