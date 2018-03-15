#include <iostream>
#include "FractalCreator.hpp"
#include "RGB.hpp"
#include "Zoom.hpp"

int main(){
    FractalCreator fractalCreator(800, 600);


    fractalCreator.colorRange(0.0, RGB(152,30,50));
    fractalCreator.colorRange(0.3, RGB(79,134,142));
    fractalCreator.colorRange(0.5, RGB(198,146,20));
    fractalCreator.colorRange(1.0, RGB(94,106,113));



    fractalCreator.addZoom(Zoom(295, 202, 0.1));
    // fractalCreator.addZoom(Zoom(312, 304, 0.1));
    fractalCreator.run("test.bmp");
    std::cout << "Finished" << std::endl;
    return 0;
}