#include <iostream>
#include <string>
#include <cmath>

#include "correcter.hpp"

using namespace std;

// Cartesian coordinate to cylindrical 
PosRad Cart2Rad(PosCart in)
{
    PosRad out;
    double x = (double) in.x;
    double y = (double) in.y;
    double r = sqrt(x*x+y*y);
    double t = atan(y/x);
    out.t = t;
    out.r = r;
    return out;
}

// Cylindrical coordinates to cartesian
PosCart Rad2Cart(PosRad in)
{
    PosCart out;
    double r = (double) in.r;
    double t = (double) in.t;
    double x = r*cos(t);
    double y = r*sin(t);
    out.x = (int) x;
    out.y = (int) y;
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
    int sizex = in.size().width, sizey = in.size().height;
    double rMax = sqrt((double) sizex * (double) sizex + (double) sizey * (double) sizey)/2.0;
    Mat out(in.size(), CV_8UC3, Scalar(0,0,0));
    for(int y = 0; y < sizey; y++)
    {
        for(int x = 0; x < sizex; x++)
        {
            PosCart srcCoord = {x,y};
            PosRad radCoord = Cart2Rad(srcCoord);
            PosCart dstCoord = Rad2Cart(radCoord);
            //cout << dstCoord.y+sizey/2 << "," << dstCoord.x+sizex/2 << endl;
            int dstX = dstCoord.x;
            int dstY = dstCoord.y;
            if(dstX < 0 || dstX >= sizex || dstY < 0 || dstY >= sizey)
            {
                cout << dstX << "," << dstY << endl;
                break;
            }
            if(dstX != x || dstY != y)
            {
                cout << x << "->" << dstX << " \t" << y << "->" << dstY << endl;
            }
            out.at<Vec3b>(dstY,dstX) = in.at<Vec3b>(y,x);
        }
    }
    return out;
}