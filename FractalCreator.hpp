#ifndef FRACTALCREATOR_HPP
#define FRACTALCREATOR_HPP

#include <string>
#include <cmath>
#include <cstdint>
// #include "Mandelbrot.hpp"
#include "Zoom.hpp"
#include "Bitmap.hpp"
#include "ZoomList.hpp"


class FractalCreator{
private:
    int m_width;
    int m_height;

    std::unique_ptr<int[]> m_histogram;
    std::unique_ptr<int[]> m_fractal;

    Bitmap m_bitmap;
    ZoomList m_zoomList;
    int m_total{0};

public:
    FractalCreator(int width, int height);
    ~FractalCreator();

    void calculateIterations();
    void drawFractal();
    void writeBitmap(std::string name);
    void addZoom(const Zoom& zoom);
    void calculateTotalIterations();

};
#endif