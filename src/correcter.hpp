#include <opencv/cv.hpp>

using namespace cv;

// Cartesian coordianate representation
typedef struct {
    int x;
    int y;
} PosCart;

// Cylindrical coordinate representation
typedef struct {
    double t;
    double r;
} PosRad;

typedef struct {
    double a;
    double b;
    double c;
} LCParam;

PosRad Cart2Rad(PosCart in);
PosCart Rad2Cart(PosRad in);
double rDistortion(double r, LCParam p);
Mat correctedImage(Mat in, LCParam p);