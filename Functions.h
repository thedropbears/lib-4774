#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace lib4774 {
	float scaleJoystick(float joystick_value, float exponential, float deadzone = 0);
	double* fieldOrient(float yaw_angle, double* to_orient);

	float r2d(float);
	float d2r(float);
}
#endif
