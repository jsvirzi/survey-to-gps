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

double haversin(double lat1, double lon1, double lat2, double lon2)
{
    // const double R = 6371000.0; /* meters */
    const double R = 3961.0 * 5280.0; /* feet */
    // double d = R * (sin(lat2 - lat1) + cos(lat2) * cos(lat1) * sin(lon2 - lon1));
    lat1 = M_PI * lat1 / 180.0;
    lon1 = M_PI * lon1 / 180.0;
    lat2 = M_PI * lat2 / 180.0;
    lon2 = M_PI * lon2 / 180.0;
    double s1 = sin(0.5 * (lat2 - lat1));
    double s2 = sin(0.5 * (lon2 - lon1));
    double c1 = cos(lat1);
    double c2 = cos(lat2);
    double factor = asin(sqrt(s1 * s1 + c1 * c2 * s2 * s2));
    double d = 2.0 * R * factor;
    return d;
}

int main(int argc, char **argv) {

    char *filename = "property.csv";
    FILE *fp = fopen(filename, "w");

#if 0
    NEBRASKA, USA (Latitude : 41.507483, longitude : -99.436554) and
    KANSAS, USA (Latitude : 38.504048, Longitude : -98.315949)
    WEST VIRGINIA (Latitude : 37.765712, Longitude : -80.849270)
#endif

    double lat1 = 37.765712, lat2;
    double lon1 = -80.849270, lon2;
    double hlat = 0.000001;
    double hlon = 0.000001;

    lat2 = lat1;
    lon2 = lon1 + hlon;
    double dlon0 = haversin(lat1, lon1, lat2, lon2);

    lat2 = lat1 + hlat;
    lon2 = lon1;
    double dlat0 = haversin(lat1, lon1, lat2, lon2);
    printf("haversin = %f, %f\n", dlat0, dlon0);

    survey_point_t *p = points;
	double x0 = 0.0;
	double y0 = 0.0;
	double x = x0;
	double y = y0;
    double lat = 37.76006;
    double lon = -80.85040;
	int k = 0;
    fprintf(fp, "id, lat, lon\n");
	for (p = points; p->distance > 0.0; ++p, ++k) {
        printf("%d: x=%f, y=%f. gps = (%f, %f)\n", k, x, y, lat, lon);
        fprintf(fp, "%d, %f, %f\n", k, lat, lon);
		double degrees = p->degrees + p->minutes / 60.0 + p->seconds / 3600.0;
		double radians = M_PI * degrees / 180.0;
		double dx = p->distance * sin(radians);
		double dy = p->distance * cos(radians);
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
        double dlat = hlat * dy / dlat0;
        double dlon = hlon * dx / dlon0;
        double distance = haversin(lat + dlat, lon + dlon, lat, lon);
        printf("distances = %f vs %f\n", distance, p->distance);
        lat += dlat;
        lon += dlon;
	}

    fclose(fp);

	return 0;
}


