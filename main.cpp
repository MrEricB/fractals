#include <iostream>
#include <cstdint> //unit8_t and others
#include <memory>
#include <cmath>
#include "Bitmap.hpp"
#include "Mandelbrot.hpp"
#include "ZoomList.hpp"

int main(){

    int const WIDTH = 800;
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    bitmap.setPixel(WIDTH/2, HEIGHT/2, 255, 255, 255);

    //double min = 999999;
    //double max = -999999;

    ZoomList zoomList(WIDTH, HEIGHT);

    //where to zoom around, first is the center are points on fractal to zoom around.
    zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/WIDTH));
    zoomList.add(Zoom(295, HEIGHT-202, 0.1));
    zoomList.add(Zoom(312, HEIGHT - 304, 0.1));

    //iterations per pixel
    std::unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_INTERATIONS]{0});
    std::unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0}); //number of iterations per pixal
    
    //store information to dwaw pixels (in other nexted for loops)
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){

            std::pair<double, double> coords = zoomList.doZoom(x,y);

            int iterations = Mandelbrot::getInterations(coords.first, coords.second);

            fractal[y*WIDTH+x] = iterations;

            if(iterations != Mandelbrot::MAX_INTERATIONS){
                histogram[iterations]++;
            }

        }
    }

    int total = 0;
    for(int i = 0; i < Mandelbrot::MAX_INTERATIONS; i++){
        total += histogram[i];
    }


    //draw the pixels
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = fractal[y*WIDTH+x];

            //pixels with max iterations are set to black.
            if(iterations != Mandelbrot::MAX_INTERATIONS){
                double hue = 0.0;
                for(int i = 0; i <= iterations; i++){
                    hue += ((double)histogram[i])/total;
                }

                green = pow(255, hue);
            }

            bitmap.setPixel(x,y, red, green, blue);
        }
    }

    bitmap.write("test.bmp");

    std::cout << "Finished" << std::endl;
    return 0;
}