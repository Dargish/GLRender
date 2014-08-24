#include <math.h>
#include <algorithm>

#define EPSILON 0.000003f
#define QUARTER_PI 0.78539816339f
#define HALF_PI 1.57079632679f
#define PI 3.14159265359f
#define PI2 6.28318530718f
#define PITCH_LIMIT 1.57f
#define ROTATE_SPEED 0.01f
#define MOVEMENT_SPEED 100.0f
#define ZOOM_SPEED 1.0f
#define PAN_SPEED 0.5f

inline float wrapAngle(float x)
{
	while (x < -PI)
	{
		x += PI2;
	}
	while (x > PI)
	{
		x -= PI2;
	}
	return x;
}

inline float constrainAngle(float x, float max = HALF_PI - EPSILON, float min = EPSILON - HALF_PI)
{
	x = std::min(x, max);
	x = std::max(x, min);
	return x;
}