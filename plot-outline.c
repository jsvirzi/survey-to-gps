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
    { 371.25, 74, 12, 5, "SE" },
    { 82.5, 59, 47, 55, "SW" },
    { 57.75, 84, 47, 55, "SW" },
    { 132.0, 24, 47, 55, "SW"},
    { 57.75, 67, 47, 55, "SW" },
    { 231.0, 76, 42, 5, "SE" },
    { 363.0, 2, 42, 5, "SE" },
    { 354.37, 58, 23, 13, "SW" },
    { 406.19, 7, 22, 28, "SE" },
    { 570.64, 63, 37, 1, "SW" },
    { 1065.68, 10, 55, 24, "SE" },
    { 99.35, 66, 7, 58, "NE" },
    { 75.63, 66, 7, 58, "NE" },
    { 73.05, 75, 33, 58, "NE" },
    { 162.07, 85, 7, 33, "NE" },
    { 87.24, 34, 48, 10, "NE" },
    { 40.94, 38, 36, 51, "NE" },
    { 20.25, 67, 39, 18, "NE" },
    { 65.26, 70, 55, 46, "NE" },
    { 57.89, 60, 6, 53, "NE" },
    { 44.83, 88, 55, 26, "SE" },
    { 32.64, 24, 52, 19, "SE" },
    { 69.26, 76, 7, 39, "SE" },
    { 109.24, 80, 30, 1, "NE" },
    { 228.71, 60, 55, 30, "NW" },
    { 44.57, 58, 12, 45, "NE" },
    { 239.49, 86, 59, 43, "SE" },
    { 902.72, 37, 28, 26, "SE" },
    { 89.85, 78, 49, 43, "NW" },
    { 212.45, 88, 8, 58, "SW" },
    { 119.03, 81, 19, 45, "SW" },
    { 506.46, 63, 6, 56, "SW" },
    { 190.48, 75, 18, 48, "SW" },
    { 216.30, 84, 52, 22, "SW" },
    { 322.99, 48, 51, 13, "SW" },
    { 126.71, 87, 42, 11, "SW" },
    { 104.67, 75, 7, 37, "NW" },
    { 274.39, 68, 22, 4, "SW" },
    { 104.0, 83, 43, 35, "NW" },
    { 609.18, 24, 26, 16, "NE" },
    { 431.90, 48, 1, 15, "NW" },
    { 423.06, 21, 40, 48, "NW" },
    { 100.60, 49, 36, 1, "SW" },
    { 218.37, 68, 28, 35, "SW" },
    { 325.45, 27, 52, 55, "SW" },
    { 83.85, 60, 57, 23, "SW" },
    { 118.06, 69, 24, 50, "SW" },
    { 163.59, 58, 16, 12, "SW" },
    { 214.16, 12, 39, 38, "SW" },
    { 623.11, 85, 2, 54, "NW" },
    { 38.44, 47, 11, 49, "NE" },
    { 33.21, 70, 52, 27, "NW" },
    { 67.08, 29, 22, 5, "NW" },
    { 29.81, 20, 6, 16, "NW" },
    { 29.87, 1, 5, 6, "NW" },
    { 27.45, 15, 57, 48, "NE" },
    { 70.73, 33, 40, 59, "NE" },
    { 31.40, 26, 31, 15, "NE" },
    { 54.06, 21, 4, 59, "NE" },
    { 23.31, 11, 19, 48, "NE" },
    { 26.48, 6, 34, 34, "NW" },
    { 26.42, 24, 55, 20, "NW" },
    { 23.52, 67, 41, 53, "NW" },
    { 16.72, 48, 26, 27, "NE" },
    { 160.02, 48, 26, 27, "NE" },
    { 27.91, 21, 29, 21, "NW" },
	{ 0.0, 0, 0, 0, "XX" }
};

/*
 * @brief haversin formula adapted from https://www.igismap.com/haversine-formula-calculate-geographic-distance-earth/
 *
 * @param lat1 latitude for first point (in degrees)
 * @param lon1 longitude for first point (in degrees)
 * @param lat2 latitude for second point (in degrees)
 * @param lon2 longitude for second point (in degrees)
 */
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
    printf("%d: x=%f, y=%f. gps = (%f, %f)\n", k, x, y, lat, lon);
    fprintf(fp, "%d, %f, %f\n", k, lat, lon);

    fclose(fp);

	return 0;
}


