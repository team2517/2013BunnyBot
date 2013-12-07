#include "WPILib.h"
#include "math.h"
#define x			0
#define y			1
#define FL			0
#define FR			1
#define BR			2
#define BL			3
#define mag			2
#define theta		3

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
		float wheelVec[4][4];
		int i;
		int j;
		const float PI = 3.1415926535;
		
		while (IsOperatorControl()) 
		{
			Watchdog().Feed();
			
			leftStickVec[x] = stick.GetRawAxis(1);
			leftStickVec[y] = stick.GetRawAxis(2);
			phi = stick.GetRawAxis(3); //Should be right stick x.
			
			//Need to change these values based on center/wheel placement.
			wheelVec[FL][x] = .707 * phi;
			wheelVec[FL][y] = .707 * phi;
			wheelVec[FR][x] = .707 * phi;
			wheelVec[FR][y] = -.707 * phi;
			wheelVec[BL][x] = -.707 * phi;
			wheelVec[BL][y] = -.707 * phi;
			wheelVec[BR][x] = -.707 * phi;
			wheelVec[BR][y] = .707 * phi;
			
			wheelVec[FL][x] += leftStickVec[x];
			wheelVec[FL][y] += leftStickVec[y];
			wheelVec[FR][x] += leftStickVec[x];
			wheelVec[FR][y] += leftStickVec[y];
			wheelVec[BL][x] += leftStickVec[x];
			wheelVec[BL][y] += leftStickVec[y];
			wheelVec[BR][x] += leftStickVec[x];
			wheelVec[BR][y] += leftStickVec[y];
			
			for(i = 0; i <= 3; i++)
			{
				wheelVec[i][mag] = sqrt(pow(wheelVec[i][x], 2) 
						+ pow(wheelVec[i][y], 2));
			}
			
			for(i = 0; i <= 3; i++)
			{
				if(wheelVec[i][mag] > 1)
				{
					for(j = 0; j <= 3; j++)
					{
						wheelVec[j][mag] = wheelVec[j][mag] / wheelVec[i][mag];
					}
				}
				
			}
			
			for(i = 0; i <= 3; i++)
			{
				wheelVec[i][theta] = atan(wheelVec[i][y] / wheelVec[i][x]);
				
				if(wheelVec[i][x] < 0)
				{
					wheelVec[i][theta] += PI;
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

