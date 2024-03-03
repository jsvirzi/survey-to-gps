#include <math.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	double distance;
    char ns[2];
	double degrees;
	double minutes;
	double seconds;
    char ew[2];
    char *description;
} survey_point_t;

survey_point_t points[] = {
    { 90.0, "S", 14, 47, 0, "W", "I-20" },
    { 80.0, "S", 88, 06, 0, "W", NULL },
    { 183.76, "N", 40, 02, 0, "W", NULL },
    { 226.92, "S", 77, 0, 0, "E", NULL },
    { 0.0 }
};

survey_point_t points_mountain[] = {
	{ 1584.76, "N", 21, 29, 21, "W", NULL },
	{ 884.45, "N", 22, 5, 12, "W", NULL },
	{ 514.36, "N", 24, 36, 14, "E", NULL },
	{ 298.22, "S", 74, 57, 13, "E", NULL },
	{ 2428.13, "N", 58, 47, 55, "E", NULL },
	{ 769.0, "S", 36, 42, 5, "E", NULL },
    { 371.25, "S", 74, 12, 5, "E", NULL },
    { 82.5, "S", 59, 47, 55, "W", NULL },
    { 57.75, "S", 84, 47, 55, "W", NULL },
    { 132.0, "S",24, 47, 55, "W", NULL },
    { 57.75, "S", 67, 47, 55, "W", NULL },
    { 231.0, "S", 76, 42, 5, "E", NULL },
    { 363.0, "S", 2, 42, 5, "E", NULL },
    { 354.37, "S", 58, 23, 13, "W", NULL },
    { 406.19, "S", 7, 22, 28, "E", NULL },
    { 570.64, "S", 63, 37, 1, "W", NULL },
    { 1065.68, "S", 10, 55, 24, "E", "down-mountain" },
    { 99.35, "N",  66, 7, 58, "E", NULL },
    { 75.63, "N", 66, 7, 58, "E", NULL },
    { 73.05, "N", 75, 33, 58, "E", NULL },
    { 162.07, "N", 85, 7, 33, "E", NULL },
    { 87.24, "N", 34, 48, 10, "E", NULL },
    { 40.94, "N", 38, 36, 51, "E", NULL },
    { 20.25, "N", 67, 39, 18, "E", NULL },
    { 65.26, "N", 70, 55, 46, "E", NULL },
    { 57.89, "N", 60, 6, 53, "E", NULL },
    { 44.83, "S", 88, 55, 26, "E", NULL },
    { 32.64, "S", 24, 52, 19, "E", NULL },
    { 69.26, "S", 76, 7, 39, "E", NULL },
    { 30.56, "N", 71, 48, 32, "E", "missing" }, /* on map, but not deed */
    { 109.24, "N", 80, 30, 1, "E", NULL },
//    { 228.71, "N", 60, 55, 30, "W", NULL }, /* orientation? */
    { 228.71, "S", 60, 55, 30, "E", NULL },
    { 44.57, "N", 58, 12, 45, "E", NULL },
    { 239.49, "S", 86, 59, 43, "E", NULL },
    { 902.72, "S", 37, 28, 26, "E", "up-mountain" },
//    { 89.85, "N", 78, 49, 43, "W", "near-waterfall" },
    { 212.45, "S", 88, 8, 58, "W", NULL },
    { 119.03, "S", 81, 19, 45, "W", NULL },
    { 506.46, "S", 63, 6, 56, "W", NULL },
    { 190.48, "S", 75, 18, 48, "W", NULL },
    { 216.30, "S", 84, 52, 22, "W", NULL },
    { 322.99, "S", 48, 51, 13, "W", NULL },
    { 126.71, "S", 87, 42, 11, "W", NULL }, /* end of page */
    { 104.67, "N", 75, 7, 37, "W", NULL },
    { 274.39, "S", 68, 22, 4, "W", NULL },
    { 104.0, "N", 83, 43, 35, "W", NULL },
//    { 609.18, "N", 24, 26, 16, "E", NULL },
    { 431.90, "N", 48, 1, 15, "W", "down-along-ridge" },
    { 423.06, "N", 21, 40, 48, "W", "down-from-ridge" },
    { 100.60, "S", 49, 36, 1, "W", NULL },
    { 218.37, "S", 68, 28, 35, "W", NULL },
    { 325.45, "S", 27, 52, 55, "W", NULL },
    { 83.85, "S", 60, 57, 23, "W", NULL },
    { 118.06, "S", 69, 24, 50, "W", NULL },
    { 163.59, "S", 58, 16, 12, "W", NULL },
    { 214.16, "S", 12, 39, 38, "W", NULL },
    { 623.11, "N", 85, 2, 54, "W", NULL },
//    { 38.44, "N", 47, 11, 49, "E", NULL },
    { 33.21, "N", 70, 52, 27, "W", NULL },
    { 67.08, "N", 29, 22, 5, "W", NULL },
    { 29.81, "N", 20, 6, 16, "W", NULL },
    { 29.87, "N", 1, 5, 6, "W", NULL },
    { 27.45, "N", 15, 57, 48, "E", NULL },
    { 70.73, "N", 33, 40, 59, "E", NULL },
    { 31.40, "N", 26, 31, 15, "E", NULL },
    { 54.06, "N", 21, 4, 59, "E", NULL },
    { 23.31, "N", 11, 19, 48, "E", NULL },
    { 26.48, "N", 6, 34, 34, "W", NULL },
    { 26.42, "N", 24, 55, 20, "W", NULL },
    { 23.52, "N", 67, 41, 53, "W", NULL },
    { 16.72, "N", 48, 26, 27, "E", NULL },
    { 160.02, "N", 48, 26, 27, "E", NULL },
    { 27.91, "N", 21, 29, 21, "W", NULL },
	{ 0.0 }
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

//    double lat1 = 37.765712, lat2; /* mountain */
//    double lon1 = -80.849270, lon2; /* mountain */
    double lat1 = 37.682496, lat2;
    double lon1 = -80.875782, lon2;
    double hlat = 0.000001;
    double hlon = 0.000001;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "-lat") == 0) {
            snprintf(argv[++i], "%f", &lat1);
        } else if (strcmp(argv[i], "-lon") == 0) {
            snprintf(argv[++i], "%f", &lon1);
        }
    }

    FILE *fp = fopen(filename, "w");

#if 0
    NEBRASKA, USA (Latitude : 41.507483, longitude : -99.436554) and
    KANSAS, USA (Latitude : 38.504048, Longitude : -98.315949)
    WEST VIRGINIA (Latitude : 37.765712, Longitude : -80.849270)
#endif

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
//    double lat = 37.76006;
//    double lon = -80.85040;
    double lat = 37.6827565;
    double lon = -80.8756773;
    double degrees0 = -0.0;
	int k = 0;
    fprintf(fp, "id, lat, lon\n");
    double total_degrees = 0.0;
	for (p = points; p->distance > 0.0; ++p, ++k) {
        printf("%d: x=%f, y=%f. gps = (%f, %f)\n", k, x, y, lat, lon);
        if (p->description == NULL) {
            fprintf(fp, "%d, %f, %f\n", k, lat, lon);
        } else {
            fprintf(fp, "\"%s\", %f, %f\n", p->description, lat, lon);
        }
		double degrees = p->degrees + p->minutes / 60.0 + p->seconds / 3600.0;
        degrees += degrees0;
		double radians = M_PI * degrees / 180.0;
		double dx = p->distance * sin(radians);
		double dy = p->distance * cos(radians);
		if (strcmp(p->ew, "W") == 0) { dx = -dx; }
		if (strcmp(p->ns, "S") == 0) { dy = -dy; }
		x += dx;
		y += dy;
        int north = (strcmp(p->ns, "N") == 0) ? 1 : 0;
        int west = (strcmp(p->ew, "W") == 0) ? 1 : 0;
        if ((north == 1) && (west == 1)) {
        } else if ((north == 0) && (west == 1)) {
            degrees = 180.0 - degrees;
        } else if ((north == 1) && (west == 0)) {
            degrees = - degrees;
        } else if ((north == 0) && (west == 0)) {
            degrees = 180.0 + degrees;
        }
        total_degrees += degrees;
        double dlat = hlat * dy / dlat0;
        double dlon = hlon * dx / dlon0;
        double distance = haversin(lat + dlat, lon + dlon, lat, lon);
        printf("distances = %f vs %f\n", distance, p->distance);
        lat += dlat;
        lon += dlon;
	}
    printf("%d: x=%f, y=%f. gps = (%f, %f)\n", k, x, y, lat, lon);
    fprintf(fp, "%d, %f, %f\n", k, lat, lon);
    printf("total degrees = %f\n", total_degrees);

    fclose(fp);

	return 0;
}


