#include "gui.hpp"
#include "correcter.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include <opencv/cv.hpp>

using namespace cv;

int tb_barrel;
int tb_pincushion;
int tb_wavy;

Mat src;

void dispTB(Mat imgsrc)
{
    tb_barrel = 100;
    tb_pincushion = 100;
    tb_wavy = 100;
    createTrackbar("Barrel", "Lens distortion correcter", &tb_barrel, 200, cb_tb_updated);
    createTrackbar("Pincushion", "Lens distortion correcter", &tb_pincushion, 200, cb_tb_updated);
    createTrackbar("Wavy", "Lens distortion correcter", &tb_wavy, 200, cb_tb_updated);
    src = imgsrc;
}

void cb_tb_updated( int, void* )
{
    LCParam param;
    param.a = ((double) tb_barrel - 100.0) / 100.0;
    param.b = ((double) tb_pincushion - 100.0) / 100.0;
    param.c = ((double) tb_wavy - 100.0) / 100.0;
    Mat newImg = correctedImage(src, param);
    imshow("Lens distortion correcter", newImg);
}
