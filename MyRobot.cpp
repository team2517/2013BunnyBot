#include "WPILib.h"

class RobotDemo : public SimpleRobot {
	Joystick stick;
	AnalogChannel positionEncoder; // only joystick
	CANJaguar driveLeft;
	CANJaguar driveRight;
	CANJaguar rollerLeft;
	CANJaguar rollerRight;
public:
	RobotDemo(void) :

		positionEncoder(1), driveLeft(5), driveRight(11), stick(1),
				rollerLeft(2), rollerRight(3) {
		Watchdog().SetExpiration(1);
	}

	void Autonomous(void) {

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {
		//DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		Watchdog().SetEnabled(true);
		while (IsOperatorControl()) {
			Watchdog().Feed();
			driveLeft.Set(stick.GetRawAxis(2));
			driveRight.Set(stick.GetRawAxis(4));
			//printf("Speed: %f\n", speed);
			//printf("Voltage: %f\n", voltage);
			/*dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Speed: %f",
			 speed);
			 dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Voltage: %f",
			 voltage);
			 
			 dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Diff: %f",
			 diff);
			 dsLCD->UpdateLCD();*/
			if (stick.GetRawButton(5)) {
				rollerLeft.Set(1);
				rollerRight.Set(1);}
			else{
				rollerLeft.Set(0);
				rollerRight.Set(0);
			}
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

