#include "WPILib.h"

class RobotDemo : public SimpleRobot {
	Joystick stick;
	AnalogChannel positionEncoder; // only joystick
	CANJaguar controllerLeft;
	CANJaguar controllerRight;

public:
	RobotDemo(void) :

		positionEncoder(1),
				controllerLeft(5), controllerRight(11), stick(1) {
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
			controllerLeft.Set(stick.GetRawAxis(2));
			controllerRight.Set(stick.GetRawAxis(4));
			    //printf("Speed: %f\n", speed);
				//printf("Voltage: %f\n", voltage);
				/*dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Speed: %f",
						speed);
				dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Voltage: %f",
						voltage);
				
				dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Diff: %f",
					    diff);
				dsLCD->UpdateLCD();*/
			
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

