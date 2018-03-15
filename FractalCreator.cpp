#include "FractalCreator.hpp"
#include "Mandelbrot.hpp" //VS Code says there is an error if not placed here, runs fine if in .hpp, just place it here to get ride of red lines.
#include <assert.h>

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

    // RGB startColor(0,0,0);
    // RGB endColor(152,30,50);
    // RGB colorDiff = endColor - startColor;

    //draw the pixels
    for(int y = 0; y < m_height; y++){
        for(int x = 0; x < m_width; x++){
            
            int iterations = m_fractal[y*m_width+x];
            int range = getRange(iterations);
            int rangeTotal = m_rangeTotals[range];
            int rangeStart = m_ranges[range];

            RGB& startColor = m_colors[range];
            RGB& endColor = m_colors[range+1];
            RGB colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            //pixels with max iterations are set to black.
            if(iterations != Mandelbrot::MAX_INTERATIONS){
                // double hue = 0.0;
                int totalPixels = 0;

                for(int i = rangeStart; i <= iterations; i++){
                    // hue += ((double)m_histogram[i])/m_total;
                    totalPixels += m_histogram[i];
                }


                // red = startColor.r + colorDiff.r * (double)totalPixels/rangeTotal;
                red = pow(startColor.r + colorDiff.r,(double)totalPixels/rangeTotal);
                green = pow(startColor.g + colorDiff.g, (double)totalPixels/rangeTotal);
                blue = pow(startColor.b + colorDiff.b,(double)totalPixels/rangeTotal);



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

void FractalCreator::run(std::string name){
    calculateIterations();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap("test.bmp");
}

void FractalCreator::colorRange(double rangeEnd, const RGB& rgb){
    m_ranges.push_back(rangeEnd * Mandelbrot::MAX_INTERATIONS);
    m_colors.push_back(rgb);

    if(m_GotFirstRange){
        m_rangeTotals.push_back(0);
    }

    m_GotFirstRange = true;

}

void FractalCreator::calculateRangeTotals(){
    int rangeIndex = 0;

    for(int i = 0; i < Mandelbrot::MAX_INTERATIONS; i++){
        int pixels = m_histogram[i];

        if(i >= m_ranges[rangeIndex + 1]){
            rangeIndex++;
        }

        m_rangeTotals[rangeIndex] += pixels;
    }
}

int FractalCreator::getRange(int iterations) const{
    int range = 0;

    for(int i =1; i < m_ranges.size(); i++){
        range = i;

        if(m_ranges[i] > iterations){
            break;
        }
    }

    range--;

    assert(range > -1);
    assert(range < m_ranges.size());

    return range;
}