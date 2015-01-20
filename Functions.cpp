#include "Functions.h"
#include "math.h"

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
}
