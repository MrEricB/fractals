#ifndef FRACTALCREATOR_HPP
#define FRACTALCREATOR_HPP

#include <string>
#include <cmath>
#include <cstdint>
#include <vector>
// #include <iostream>
// #include "Mandelbrot.hpp"
#include "Zoom.hpp"
#include "Bitmap.hpp"
#include "ZoomList.hpp"
#include "RGB.hpp"


class FractalCreator{
private:
    int m_width;
    int m_height;

    std::unique_ptr<int[]> m_histogram;
    std::unique_ptr<int[]> m_fractal;

    Bitmap m_bitmap;
    ZoomList m_zoomList;
    int m_total{0};

    std::vector<int> m_ranges;
    std::vector<RGB> m_colors;
    std::vector<int> m_rangeTotals;

    bool m_GotFirstRange{false};


private:
    void calculateIterations();
    void drawFractal();
    void writeBitmap(std::string name);
    void calculateTotalIterations();
    void calculateRangeTotals();
    int getRange(int iterations) const;

public:
    FractalCreator(int width, int height);
    ~FractalCreator();
    void addZoom(const Zoom& zoom);
    void run(std::string name);
    void colorRange(double rangeEnd, const RGB& rgb);

};
#endif