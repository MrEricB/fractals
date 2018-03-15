#include "FractalCreator.hpp"
#include "Mandelbrot.hpp" //VS Code says there is an error if not placed here, runs fine if in .hpp, just place it here to get ride of red lines.

FractalCreator::FractalCreator(int width, int height): m_width(width), m_height(height), m_histogram(new int[Mandelbrot::MAX_INTERATIONS]{0}), m_fractal(new int[m_width*m_height]{0}), m_bitmap(m_width, m_height), m_zoomList(m_width, m_height){

    m_zoomList.add(Zoom(m_width/2, m_height/2, 4.0/m_width));

}

FractalCreator::~FractalCreator(){

}

void FractalCreator::calculateIterations(){
    //store information to dwaw pixels (in other nexted for loops)
    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x++){

            std::pair<double, double> coords = m_zoomList.doZoom(x,y);

            int iterations = Mandelbrot::getInterations(coords.first, coords.second);

            m_fractal[y*m_width+x] = iterations;

            if(iterations != Mandelbrot::MAX_INTERATIONS){
                m_histogram[iterations]++;
            }

        }
    }
}

void FractalCreator::drawFractal(){
    //draw the pixels
    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x++){
            
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = m_fractal[y*m_width+x];

            //pixels with max iterations are set to black.
            if(iterations != Mandelbrot::MAX_INTERATIONS){
                double hue = 0.0;
                for(int i = 0; i <= iterations; i++){
                    hue += ((double)m_histogram[i])/m_total;
                }

                green = pow(255, hue);
                //green = hue * 255;
            }

            m_bitmap.setPixel(x,y, red, green, blue);
        }
    }
}

void FractalCreator::writeBitmap(std::string name){
    m_bitmap.write(name);
}

void FractalCreator::addZoom(const Zoom& zoom){
    m_zoomList.add(zoom);
}

void FractalCreator::calculateTotalIterations(){
    for(int i = 0; i < Mandelbrot::MAX_INTERATIONS; i++){
        m_total += m_histogram[i];
    }
}