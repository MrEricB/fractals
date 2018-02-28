#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP


class Mandelbrot{
public: 
    static const int MAX_INTERATIONS = 1000; //more iterations means "nicer looking" fractaial, but time to draw increases

public:
    Mandelbrot();
    virtual ~Mandelbrot();

    static int getInterations(double x, double y);
};

#endif