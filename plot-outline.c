#include <math.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	double distance;
	double degrees;
	double minutes;
	double seconds;
	char *dir;
} survey_point_t;

survey_point_t points[] = {
	{ 1584.76, 21, 29, 21, "NW" },
	{ 884.45, 22, 5, 12, "NW" },
	{ 514.36, 24, 36, 14, "NE" },
	{ 298.22, 74, 57, 13, "SE" },
	{ 2428.13, 58, 47, 55, "NE" },
	{ 769.0, 36, 42, 5, "SE" },
	{ 0.0, 0, 0, 0, "XX" }
};

int main(int argc, char **argv) {
	survey_point_t *p = points;
	double x0 = 0.0;
	double y0 = 0.0;
	double x = x0;
	double y = y0;
	int k = 0;
	for (p = points; p->distance > 0.0; ++p, ++k) {
		double degrees = p->degrees + p->minutes / 60.0 + p->seconds / 3600.0;
		double radians = M_PI * degrees / 180.0;
		double dx = p->distance * cos(radians);
		double dy = p->distance * sin(radians);
		if (strcmp(p->dir, "NW") == 0) {
			dx = -dx;
		} else if (strcmp(p->dir, "SW") == 0) {
			dx = -dx;
			dy = -dy;
		} else if (strcmp(p->dir, "NE") == 0) {
		} else if (strcmp(p->dir, "SE") == 0) {
			dy = -dy;
		}
		x += dx;
		y += dy;
		printf("%d: x=%f, y=%f\n", k, x, y); 
	}
	return 0;
}

