#include <iostream>
#include <string>
#include <cmath>

#include "correcter.hpp"
#include "gui.hpp"

#include <opencv/cv.hpp>

using namespace std;
using namespace cv;



int main(int argc, char const *argv[])
{
    String imageName("../pictures/checkerboard.jpg"); // by default
    Mat image;
    image = imread(imageName, IMREAD_COLOR); // Read the file
    if(image.empty())                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    Mat newImg = correctedImage(image, {0.0, 0.0, 0.0});

    namedWindow("Lens distortion correcter", WINDOW_AUTOSIZE ); // Create a window for display.
    dispTB(image);
    imshow("Lens distortion correcter", newImg);                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}

