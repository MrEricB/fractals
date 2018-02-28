#include <iostream>
#include <cstdint>
#include "Bitmap.hpp"
#include "Mandelbrot.hpp"

int main(){

    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    bitmap.setPixel(WIDTH/2, HEIGHT/2, 255, 255, 255);

    double min = 999999;
    double max = -999999;

    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){

            double xFrac = (x - WIDTH/2) * 2.0/WIDTH; //max xFac [-1,1]
            double yFrac = (y - HEIGHT/2) * 2.0/HEIGHT;

            int iterations = Mandelbrot::getInterations(xFrac, yFrac);

            uint8_t red = (uint8_t)(256 * (double)iterations/Mandelbrot::MAX_INTERATIONS);

            bitmap.setPixel(x,y, red, red, red);

            if(red < min){ min = red;}
            if(red > max){max = red;}

        }
    }

    
    std::cout << min  << ", " << max << std::endl;

    bitmap.write("test.bmp");

    std::cout << "Finished" << std::endl;
    return 0;
}