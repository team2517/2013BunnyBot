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

	void Autonomous(void) {
		autoTimer.Start();
		while (true) {
			if (autoTimer.Get() < 10) {
				driveLeft.Set(1);
				driveRight.Set(1);
			} else {
				driveLeft.Set(0);
				driveRight.Set(0);
			}
			if (autoTimer.Get()>14) {
				bunnyDropFront.Set(1);
			} else {
				bunnyDropFront.Set(0);
			}
		}
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {
		DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		Watchdog().SetEnabled(true);
		float leftSpeed, rightSpeed;
		bool button6Pressed, button8Pressed, button5Pressed, button7Pressed;

		while (IsOperatorControl()) {
			Watchdog().Feed();

			if (stick.GetRawButton(6) && rightSpeed < 1 && button6Pressed
					== false) {
				rightSpeed += .05;
				button6Pressed = true;
			} else if (stick.GetRawButton(6)==false) {
				button6Pressed = false;
			}
			if (stick.GetRawButton(8) && rightSpeed > -1 && button8Pressed
					== false) {
				rightSpeed -= .05;
				button8Pressed = true;
			} else if (stick.GetRawButton(8)==false) {
				button8Pressed = false;
			}

			if (stick.GetRawButton(5) && leftSpeed < 1 && button5Pressed
					== false) {
				leftSpeed += .05;
				button5Pressed = true;
			} else if (stick.GetRawButton(5)==false) {
				button5Pressed = false;
			}
			if (stick.GetRawButton(7) && leftSpeed > -1 && button7Pressed
					== false) {
				leftSpeed -= .05;
				button7Pressed = true;
			} else if (stick.GetRawButton(7)==false) {
				button7Pressed = false;
			}
			
			if(stick.GetRawButton(2))
			{
				driveLeft.Set(leftSpeed);
				driveRight.Set(rightSpeed);
			}
			else
			{
				driveLeft.Set(0);
				driveRight.Set(0);
			}

			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1,
					"rightSpeed = %f, leftSpeed = %f", rightSpeed, leftSpeed);
			dsLCD->UpdateLCD();
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo)
;

