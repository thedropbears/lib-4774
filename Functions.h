#ifndef FUNCTIONS_H
#define FUNCTIONS_H

namespace lib4774 {
enum joystick_axis {
    X,
    Y
};

	float scaleJoystick(float joystick_value, float exponential, float deadzone = 0);
	float fieldOrient(lib4774::joystick_axis axis, float yaw_angle, float vX, float vY);

	float r2d(float);
	float d2r(float);
}
#endif
