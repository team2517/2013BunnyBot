#include "WPILib.h"

class RobotDemo : public SimpleRobot {
	Encoder speedEncoder; //comments are cool
	Joystick stick;
	AnalogChannel positionEncoder; // only joystick
	CANJaguar controller;
	CANJaguar controller5;

public:
	RobotDemo(void) :

		speedEncoder(1, 2, false, Encoder::k1X), positionEncoder(1),
				controller(5), controller5(11), stick(1) {
		//		myRobot.SetExpiration(0.1);
	}

	void Autonomous(void) {

	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void) {
		double TarAngle = 2;
		DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		speedEncoder.SetDistancePerPulse(1.0);
		speedEncoder.Start();
		double diff;
		while (IsOperatorControl()) {
			controller.Set(stick.GetRawAxis(1));
			double speed = speedEncoder.GetRate();
			float voltage = positionEncoder.GetVoltage();
			diff = voltage - TarAngle;
			if (TarAngle > voltage) {
				if (diff > 2.5)
					controller5.Set(.1);
				else
					controller5.Set(-.1);
			} else if (TarAngle < voltage) {
				if (diff < -2.5)
					controller5.Set(-.1);
				else
					controller5.Set(.1);
			} else
				controller5.Set(0);
			
				//printf("Speed: %f\n", speed);
				//printf("Voltage: %f\n", voltage);
				dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Speed: %f",
						speed);
				dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Voltage: %f",
						voltage);
				
				dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Diff: %f",
					    diff);
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

