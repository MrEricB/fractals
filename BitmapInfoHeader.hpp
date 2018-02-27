#ifndef BITMAPINFOHEADER_HPP
#define BITMAPINFOHEADER_HPP

#include <cstdint>
#pragma pack(2)

struct BitmapInfoHeader {
    int32_t headerSize{40}; //size of this struct
    int32_t width; // width and height of actual bitmaps
    int32_t height;
    int16_t planes{1}; //found on msdn.microsoft.com, must be 1;
    int16_t bitsPerPixel{24}; //1 byte for each RRG thus 24
    int32_t compression{0}; // no compression
    int32_t dataSize{0}; 
    int32_t horizontalResolution{2400};
    int32_t verticalResolution{2400};
    int32_t colors{0}; //The number of color indexes in the color table that are actually used by the bitmap. If this value is zero, the bitmap uses the maximum number of colors corresponding to the value of the biBitCount member for the compression mode specified by biCompression.
    int32_t importantColors{0}; //The number of color indexes that are required for displaying the bitmap. If this value is zero, all colors are required.


};



#endif