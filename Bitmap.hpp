#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <string>
#include <cstdint>

class Bitmap {
private:
    int m_width{0};
    int m_height{0};
    std::unique_ptr<uint8_t[]>  m_pPixels{nullptr};
public:
    Bitmap(int width, int height);
    ~Bitmap();
    bool write(std::string filename);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

};


#endif