#include Functions.h

namespace lib-4774{
	float scaleJoystick (float joystick_value, float exponential, float deadzone)
	{
		double a = log(exponential+1)/(1-deadzone);
		if (joystick_value > 0) {
			float joystick_scaled = (exp(a*(joystick_value - deadzone))-1)/exponential;
		} else {
			float joystick_scaled = -(exp(a*-(joystick_value + deadzone))-1)/exponential;
		}
		return joystick_scaled;
	}
}
