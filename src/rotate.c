#include "../inc/fdf.h"

// rotate
t_point	rotate_x(t_point p, float angle_x)
{
	t_point	rotated;

	rotated.x = p.x;
	rotated.y = p.y * cos(angle_x) - p.z * sin(angle_x);
	rotated.z = p.y * sin(angle_x) + p.z * cos(angle_x);
	rotated.color = p.color;
	return (rotated);
}

t_point	rotate_y(t_point p, float angle_y)
{
	t_point	rotated;

	rotated.x = p.x * cos(angle_y) + p.z * sin(angle_y);
	rotated.y = p.y;
	rotated.z = -p.x * sin(angle_y) + p.z * cos(angle_y);
	rotated.color = p.color;
	return (rotated);
}

t_point	rotate_z(t_point p, float angle_z)
{
	t_point	rotated;

	rotated.x = p.x * cos(angle_z) - p.y * sin(angle_z);
	rotated.y = p.x * sin(angle_z) + p.y * cos(angle_z);
	rotated.z = p.z;
	rotated.color = p.color;
	return (rotated);
}
