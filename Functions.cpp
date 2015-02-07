#include "Functions.h"
#include <cmath>

namespace lib4774{
	float scaleJoystick (float joystick_value, float exponential, float deadzone)
	{
		double a = log(exponential+1)/(1-deadzone);
		float joystick_scaled = 0;
		if (joystick_value > deadzone) {
			joystick_scaled = (exp(a*(joystick_value - deadzone))-1)/exponential;
		} else if (joystick_value < -deadzone){
			joystick_scaled = -(exp(a*-(joystick_value + deadzone))-1)/exponential;
		}
		return joystick_scaled;
	}

	double* fieldOrient (float yaw_angle, double* to_orient) {
		double tempVX = to_orient[0];
		to_orient[0] = to_orient[0]*cos(yaw_angle)-to_orient[1]*sin(yaw_angle);
		to_orient[1] = tempVX*sin(yaw_angle)+to_orient[1]*cos(yaw_angle);
	    return to_orient;
	}

	float r2d(float r) {
		return r/M_PI*180.0;
	}
	float d2r(float d) {
		return d*M_PI/180.0;
	}
}
