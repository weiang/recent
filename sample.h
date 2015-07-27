#include <math.h>


extern int gcd(int, int y);

extern int in_mandel(double, double, int);

extern int divide(int, int, int*);

extern double avg(double*, int);

typedef struct Point {
	double x, y;
} Point;

extern double distance(Point*, Point*);