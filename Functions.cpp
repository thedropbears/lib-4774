#include "Functions.h"
#include <cmath>

namespace lib4774{
	float scaleJoystick (float joystick_value, float exponential, float deadzone, float scale)
	{
		double a = log(exponential+1)/(1-deadzone);
		float joystick_scaled = 0;
		if (joystick_value > deadzone) {
			joystick_scaled = (exp(a*(joystick_value - deadzone))-1)/exponential;
		} else if (joystick_value < -deadzone){
			joystick_scaled = -(exp(a*-(joystick_value + deadzone))-1)/exponential;
		}
		return (joystick_scaled*scale);
	}

	void fieldOrient (float vX, float vY, float yaw_angle, double* result) {
		result[0] = vX*cos(yaw_angle)-vY*sin(yaw_angle);
		result[1] = vX*sin(yaw_angle)+vY*cos(yaw_angle);
	}

	float r2d(float r) {
		return r/M_PI*180.0;
	}
	float d2r(float d) {
		return d*M_PI/180.0;
	}
}
