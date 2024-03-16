#include "Animation.h"

float Animation::animate(float target, float current, float speed)
{
	if (speed < 0)
		speed = 0;
	else if (speed > 1)
		speed = 1;

	float dif = max(target, current) - min(target, current);
	float factor = dif * speed;
	if (factor < 0.1f)
		factor = 0.1f;

	current = (target > current) ? (current += factor) : (current -= factor);

	return current;
}
