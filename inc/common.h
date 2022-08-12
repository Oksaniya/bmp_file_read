#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FULL_HEADER 14
#define IDENTIFYER 2
#define FILE_IN_BYTES 4
#define RESERVED 4
#define DATA_OFFSET 4
#define INFO_HEADER 40
#define COLOR_TABLE 4

typedef struct __attribute__((packed))      s_header
{
    uint16_t            identifyer;     //2 bytes: BM * BA * CI * CP * IC * PT
    uint32_t            file_in_bytes;  // 4 bytes	The size of the BMP file in bytes
    uint32_t            reserved;       //4 bytes: unused (=0)
    uint32_t            DataOffset;     //4 bytes: Offset from beginning of file to the beginning of the bitmap data
}                                           t_header;

enum InfoHeader
{
    SIZE = 4, // 4 bytes	            Size of InfoHeader =40
    WIDTH = 4, // 4 bytes               Horizontal width of bitmap in pixels
    HEIGHT = 4, //	4 bytes             Vertical height of bitmap in pixels 
    PLANES = 2, // 2 bytes              Number of Planes (=1)
    BITS_PER_PIXEL = 2, // 2 bytes      Bits per Pixel used to store palette entry information.
    COMPREHESSION = 4, //	4 bytes     Type of Compression  
    IMAGE_SIZE = 4,	//4 bytes           Size of Image It is valid to set this =0 if Compression = 0
    X_PIXEL_PER_M = 4,	// 4 bytes      Horizontal resolution: Pixels/meter
    Y_PIXEL_PER_M = 4,	// 4 bytes      Vertical resolution: Pixels/meter
    COLOURS_USED = 4, // 4 bytes        Number of actually used colors. For a 8-bit / pixel bitmap this will be 100h or 256.
    IMPORTANT_COLOURS = 4, //4 bytes     Number of important colors 0 = all
};

typedef struct __attribute__((packed))          s_InfoHeader
{
uint32_t Size_;             // 4 bytes
uint32_t Width;	            // 4 bytes
uint32_t Height;	        // 4 bytes
uint16_t Planes;	        // 2 bytes	
uint16_t Bits_Per_Pixel;    // 2 bytes	
uint32_t Compression;       // 4 bytes	
uint32_t ImageSize;         // 4 bytes
uint32_t XpixelsPerM;       // 4 bytes	
uint32_t YpixelsPerM;       // 4 bytes	
uint32_t Colors_Used;       // 4 bytes	
uint32_t Important_Colors;  // 4 bytes
}                                               t_InfoHeader;

enum ColorTable
{
    RED = 4,        //1 byte    Red intensity
    GREEN = 4,      //1 byte    Green intensity
    BLUE = 4,       //1 byte    Blue intensity
    RESERVED1 = 2,  //1 byte    unused (=0)
};

typedef struct __attribute__((packed))          s_ColorTable
{
uint8_t Red;        // 1 byte
uint8_t Green;      // 1 byte
uint8_t Blue;       // 1 byte
uint8_t Reserved;   // 1 byte	
}                                               t_ColorTable;

void argc_check(int argc);
void header_decoder(FILE *file_pointer, t_header *header);
void InfoHeader_decoder(FILE *file_pointer, t_InfoHeader *InfoHeader);
void ColorTable_decoder(FILE *file_pointer, t_ColorTable *ColorTable);

#endif