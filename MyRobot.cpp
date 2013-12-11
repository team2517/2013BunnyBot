#include "WPILib.h"
#include "math.h"
#define X			0
#define Y			1
#define FL			0
#define FR			1
#define BR			2
#define BL			3
#define MAG			2
#define THETA		3
#define PI			3.1415926535

struct wheelVector
{
	float x, y, mag, theta;
};

class RobotDemo : public SimpleRobot {
	Joystick stick;
	CANJaguar rollerLeft;
	CANJaguar rollerRight;
	CANJaguar shootMotor;
	CANJaguar belt;
	Servo bunnyDropFront;
    Servo bunnyDropBack;
public:
	RobotDemo(void) :

		stick(1), rollerLeft(2), rollerRight(3), shootMotor(4), belt(6), 
		bunnyDropFront(1), bunnyDropBack(2) 
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
		//DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		Watchdog().SetEnabled(true);
		bool button6Pressed = false;
		bool button8Pressed = false;
		float shooterSpeed = 0.0;
		float leftStickVec[2];
		float phi;
		wheelVector wheel[4];
		int i;
		int j;
		
		while (IsOperatorControl()) 
		{
			Watchdog().Feed();
			
			leftStickVec[X] = stick.GetRawAxis(1);
			leftStickVec[Y] = stick.GetRawAxis(2);
			phi = stick.GetRawAxis(3); //Should be right stick x.
			
			//Need to change these values based on center/wheel placement.
			wheel[FL].x = .707 * phi;
			wheel[FL].y = .707 * phi;
			wheel[FR].x = .707 * phi;
			wheel[FR].y = -.707 * phi;
			wheel[BL].x = -.707 * phi;
			wheel[BL].y = -.707 * phi;
			wheel[BR].x = -.707 * phi;
			wheel[BR].y = .707 * phi;
			
			wheel[FL].x += leftStickVec[X];
			wheel[FL].y += leftStickVec[Y];
			wheel[FR].x += leftStickVec[X];
			wheel[FR].y += leftStickVec[Y];
			wheel[BL].x += leftStickVec[X];
			wheel[BL].y += leftStickVec[Y];
			wheel[BR].x += leftStickVec[X];
			wheel[BR].y += leftStickVec[Y];
			
			for(i = 0; i <= 3; i++)
			{
				wheel[i].mag = sqrt(pow(wheel[i].x, 2) 
						+ pow(wheel[i].y, 2));
			}
			
			for(i = 0; i <= 3; i++)
			{
				if(wheel[i].mag > 1)
				{
					for(j = 0; j <= 3; j++)
					{
						wheel[j].mag = wheel[j].mag / wheel[i].mag;
					}
				}
				
			}
			
			for(i = 0; i <= 3; i++)
			{
				wheel[i].theta = atan(wheel[i].y / wheel[i].x);
				
				if(wheel[i].x < 0)
				{
					wheel[i].theta += PI;
				}
			}
			
			if (stick.GetRawButton(3))
			{
				bunnyDropFront.Set(1);
			}
			if (stick.GetRawButton(4))
			{
				bunnyDropFront.Set(-1);
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

