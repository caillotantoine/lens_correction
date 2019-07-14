# lens_correction

Here is a simple example of lens distortion correction algorithm.

## Compiling

You can use the ```make mrproper all run``` command. 
Requirements : 
* pkg-config
* g++

## Source

I based the mathematical calculation on the informations given by this website: 
[Lens correction model](http://hugin.sourceforge.net/docs/manual/Lens_correction_model.html)

## next steps
* adapt to camera files
* apply different parameters for each colors (chromatique aberation correction)

## Library

[OpenCV](https://opencv.org) was used to read the image and access the pixels.


