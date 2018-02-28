#include <fstream>

#include "Bitmap.hpp"
#include "BitmapInfoHeader.hpp"
#include "BitmapFileHeader.hpp"


Bitmap::Bitmap(int width, int height): m_width(width), m_height(height), m_pPixels(new uint8_t[width*height*3]{}){
    
}

Bitmap::~Bitmap(){

}

bool Bitmap::write(std::string filename){
    
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + m_width * m_height * 3;
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader); //distfrom beginning of file to where the file starts
    

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    std::ofstream ofile;
    ofile.open(filename, std::ios::out|std::ios::binary);
    
    if(!ofile){
        return false;
    }

    ofile.write((char *)&fileHeader, sizeof(fileHeader));
    ofile.write((char *)&infoHeader, sizeof(infoHeader));
    ofile.write((char *)m_pPixels.get(), m_width*m_height*3);

    ofile.close();

    if(!ofile){
        return false;
    }

    return true;
}
void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue){
    uint8_t *pPixel = m_pPixels.get(); //pointer to memory block that represents the whole screen

    pPixel += (y*3)*m_width + (3*x);
    
    //reverse order ie is BGR not RGB because bitmap is little endian file format.
    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red; 

}