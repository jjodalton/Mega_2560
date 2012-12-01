//----------------------------------------------//
// File: Drive.cpp								//
// Description: Motor control abstraction class //
// Author: Jeremy Dalton                        //
// Creation Date: 23/10/2012                    //
//----------------------------------------------//

#include "Drive.h"
#include "Arduino.h"

#define VERSION	2.0	// Software version

#define rampDelay	10	 // Delay between speed step changes
#define RMclkPin	2	// Right Motor clock pin
#define RMdirPin	40	// Right motor direction pin
#define RMprePin	41	// Right Motor preset pin
#define LMclkPin	3	// Left Motor clock pin
#define LMdirPin	42	// Left Motor direction pin
#define LMprePin	43	// Left Motor preset pin

Drive::Drive() {

}

void Drive::fw() {
	Serial.print("Drv: ");
	Serial.print(VERSION);
	Serial.println();
}

void Drive::init(int verbose) {
	if (verbose >= 3) Serial.println("|_ Drive init...");
	Drive::RMspe = 0;
	Drive::RMdir = 0;
	Drive::RMpre = 0;
	Drive::LMspe = 0;
	Drive::LMdir = 0;
	Drive::LMpre = 0;
	Drive::BMspe = 0;
}

void Drive::forward(int verbose, int debug, int motor, int speed) {
	//Motor select options:	1=> Both only	2=> Right only	3=> Left only

	//-> Check direction is set to forwards
	//-> test current speed vs desired speed then call appropriate ramp function to change speed.

	switch (motor) {
	case 1:
		if (verbose >= 3) Serial.println("Drive Forward: Case 1 - Both Motors");
		if (RMdir == 0) {
			RMdir = 1;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Forward: Setting RMdir");
			digitalWrite(RMdirPin, RMdir);
		}
		if (LMdir == 0) {
			LMdir = 1;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Forward: Setting LMdir");
			digitalWrite(LMdirPin, LMdir);
		}

		if (speed > BMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < BMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == BMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: Nothing called");
		}
		break;

	case 2:
		if (verbose >= 3) Serial.println("Drive Forward: Case 2 - Right Motor");
		if (RMdir == 0) {
			RMdir = 1;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Forward: Setting RMdir");
			digitalWrite(RMdirPin, RMdir);
		}

		if (speed > RMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < RMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == RMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: Nothing called");
		}
		break;

	case 3:
		if (verbose >= 3) Serial.println("Drive Forward: Case 3 - Left Motor");
		if (LMdir == 0) {
			LMdir = 1;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Forward: Setting LMdir");
			digitalWrite(LMdirPin, LMdir);
		}

		if (speed > LMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < LMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == LMspe) {
			if (verbose >= 3) Serial.println("Drive Forward: Nothing called");
		}
		break;

	default:

		break;

	}
}

void Drive::backward(int verbose, int debug, int motor, int speed) {
	//Motor select options:	1=> Both only	2=> Right only	3=> Left only

	//-> Check direction is set to forwards
	//-> Each case tests current speed vs desired speed then calls then appropriate ramp function to change speed.

	switch (motor) {
	case 1:
		if (verbose >= 3) Serial.println("Drive Backward: Case 1 - Both Motors");
		if (RMdir == 1) {
			RMdir = 0;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Backward: Setting RMdir");
			digitalWrite(RMdirPin, RMdir);
		}
		if (LMdir == 1) {
			RMdir = 0;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Backward: Setting LMdir");
			digitalWrite(LMdirPin, LMdir);
		}

		if (speed > BMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < BMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == BMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: Nothing called");
		}
		break;

	case 2:
		if (verbose >= 3) Serial.println("Drive Backward: Case 1 - Both Motors");
		if (RMdir == 1) {
			RMdir = 0;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Backward: Setting RMdir");
			digitalWrite(RMdirPin, RMdir);
		}

		if (speed > RMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < RMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == RMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: Nothing called");
		}
		break;

	case 3:
		if (verbose >= 3) Serial.println("Drive Backward: Case 1 - Both Motors");
		if (LMdir == 1) {
			LMdir = 0;
			//digital write direction to pin
			if (verbose >= 3) Serial.println("Drive Backward: Setting LMdir");
			digitalWrite(LMdirPin, LMdir);
		}

		if (speed > LMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampUp called");
			rampUp(debug, speed, motor);
		}
		else if (speed < LMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: rampDown called");
			rampDown(debug, speed, motor);
		}
		else if (speed == LMspe) {
			if (verbose >= 3) Serial.println("Drive Backward: Nothing called");
		}
		break;

	default:

		break;

	}
}

void Drive::stop(int verbose, int debug, int motor = 1) {
	if (verbose >= 3) Serial.println("Stop!");
	rampDown(debug, 0, motor);
};

void Drive::rampUp(int debug, int maxSpeed, int motor) {
	//Motor select options:	1=> Both only	2=> Right only	3=> Left only	
	switch (motor) {
	case 1:
		if (debug >= 4) Serial.println("Drive rampUp: Case 1 - Both Motors");
		int i;
		for (i = BMspe; i <= maxSpeed; i++) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampUp: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(RMclkPin, i);
			analogWrite(LMclkPin, i);
		}
		i--;
		//sync new speed to BMspe
		BMspe = i;
		//sync new speed to RMspe
		RMspe = i;
		//sync new speed to LMspe
		LMspe = i;
		break;

	case 2:
		if (debug >= 4) Serial.println("Drive rampUp: Case 2 - Right Motor");
		for (int i = RMspe; i <= maxSpeed; i++) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampUp: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(RMclkPin, i);
		}
		i--;
		//sync new speed to RMspe
		RMspe = i;
		break;

	case 3:
		if (debug >= 4) Serial.println("Drive rampUp: Case 3 - Left Motor");
		for (int i = LMspe; i <= maxSpeed; i++) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampUp: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(LMclkPin, i);
		}
		i--;
		//sync new speed to LMspe
		LMspe = i;
		break;

	default:

		break;

	}
}

void Drive::rampDown(int debug, int minSpeed, int motor) {
	//Motor select options:	1=> Both only	2=> Right only	3=> Left only
	switch (motor) {
	case 1:
		int i;
		if (debug >= 4) Serial.println("Drive rampDown: Case 1 - Both Motors");
		for (i = BMspe; i >= minSpeed; i--) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampDown: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(RMclkPin, i);
			analogWrite(LMclkPin, i);
		}
		i++;
		//sync new speed to BMspe
		BMspe = i;
		//sync new speed to RMspe
		RMspe = i;
		//sync new speed to LMspe
		LMspe = i;
		break;

	case 2:
		if (debug >= 4) Serial.println("Drive rampDown: Case 2 - Right Motor");
		for (int i = RMspe; i >= minSpeed; i--) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampDown: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(RMclkPin, i);
		}
		i++;
		//sync new speed to RMspe
		RMspe = i;
		break;

	case 3:
		if (debug >= 4) Serial.println("Drive rampDown: Case 3 - Left Motor");
		for (int i = LMspe; i >= minSpeed; i--) {
			//write 'i' to output
			if (debug >= 5) Serial.print("rampDown: ");
			if (debug >= 5) Serial.print(i);
			if (debug >= 5) Serial.println();
			analogWrite(LMclkPin, i);
		}
		i++;
		//sync new speed to LMspe
		LMspe = i;
		break;

	default:

		break;

	}
}

//----------------------------------------------------------//
// But I have promises to keep, and miles to go before I	//
// sleep, and miles to go before I sleep.					//
//	-Robert Frost											//
//----------------------------------------------------------//