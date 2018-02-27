#ifndef BITMAPFILEHEADER_HPP
#define BITMAPFILEHEADER_HPP

#include <cstdint> //used to get 32bit integer exactlly and always

#pragma pack(2) //allian stuct on 2 bit bounderys, ie no padding for struck in memory. Need because this will be written to a file

struct BitmapFileHeader {
    char header[2]{'B', 'M'};
    int32_t fileSize;
    int32_t reserved{0};
    int32_t dataOffset;

};

#endif