#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace lib4774 {
	float scaleJoystick(float joystick_value, float exponential, float deadzone = 0, float scale = 1.0);
	void fieldOrient(float vX, float vY, float yaw_angle, double* result);

	float r2d(float);
	float d2r(float);
}
#endif
