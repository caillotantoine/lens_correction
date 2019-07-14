#include <iostream>
#include <string>
#include <cmath>

#include "correcter.hpp"

using namespace std;

// Cartesian coordinate to cylindrical 
PosRad Cart2Rad(PosCart in)
{
    PosRad out;
    double x = in.x;
    double y = in.y;
    double r = sqrt(x*x+y*y);
    double t = atan2(y, x);
    out.t = t;
    out.r = r;
    return out;
}

// Cylindrical coordinates to cartesian
PosCart Rad2Cart(PosRad in)
{
    PosCart out;
    double r = in.r;
    double t = in.t;
    double x = r*cos(t);
    double y = r*sin(t);
    out.x =  x;
    out.y = y;
    return out;
}

double rDistortion(double r, LCParam p)
{
    double a = p.a, b = p.b, c = p.c;
    double d = 1 - (a+b+c);
    double rr = r*r;
    double rrr = r*r*r;
    return (a*rrr + b*rr + c*r + d)*r;
}

Mat correctedImage(Mat in, LCParam p)
{
    double sizex = (double) in.size().width, sizey = (double) in.size().height;
    double rMax = sqrt(sizex * sizex + sizey * sizey)/2.0;
    Mat out(in.size(), CV_8UC3, Scalar(0,0,0));
    for(double y = 0; y < sizey; y++)
    {
        for(double x = 0; x < sizex; x++)
        {
            PosCart srcCoord = {x-sizex/2.0,y-sizey/2.0};
            PosRad radCoord = Cart2Rad(srcCoord); 
            radCoord.r = rDistortion(radCoord.r/rMax, p)*rMax;
            PosCart dstCoord = Rad2Cart(radCoord);
            double dstX = dstCoord.x+sizex/2.0;
            double dstY = dstCoord.y+sizey/2.0;
            if(isnan(dstX) || isnan(dstY))
            {
                // cout << x << "->" << dstX << " \t" << y << "->" << dstY << endl;
                dstX = x;
                dstY = y;
            }
            if(round(dstX) < 0 || round(dstX) >= sizex || round(dstY) < 0 || round(dstY) >= sizey)
            {
                // cout << dstX << ";" << dstY << endl;
                continue;
            }
            out.at<Vec3b>(round(y), round(x)) = in.at<Vec3b>(round(dstY), round(dstX));
        }
    }
    return out;
}