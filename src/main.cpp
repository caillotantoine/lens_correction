#include <iostream>
#include <string>
#include <cmath>

#include "correcter.hpp"

#include <opencv/cv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    String imageName("../pictures/bumblebee.jpg"); // by default
    Mat image;
    image = imread( imageName, IMREAD_COLOR ); // Read the file
    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    cout << image.size() << endl;

    LCParam param = {0.0, 0.0, 0.0};
    Mat newImg = correctedImage(image, param);

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", newImg);                // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}

