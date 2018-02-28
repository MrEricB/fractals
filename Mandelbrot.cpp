#include <complex> //needed for complex numbers, for mandelbrot algorithm
#include "Mandelbrot.hpp"

Mandelbrot::Mandelbrot(){

}

Mandelbrot::~Mandelbrot(){


}

int Mandelbrot::getInterations(double x, double y){

    std::complex<double> z = 0;
    std::complex<double> c(x,y);

    int iterations = 0;


    while(iterations < MAX_INTERATIONS){
        z = z*z + c;

        if(std::abs(z) > 2){
            break;
        }

        iterations++;
    }


    return iterations;
}