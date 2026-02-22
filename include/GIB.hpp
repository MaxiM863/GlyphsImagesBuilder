#ifndef GIB_HPP
#define GIB_HPP

#include <iostream>
#include <vector>
#include <fstream>

#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_truetype.h"

class GIB{

    public:

        static bool build(const char* fontFilename);

    private:

        static std::vector<unsigned char> fontBuffer;
        static stbtt_fontinfo font;

    private:

        static unsigned char* ImageData;     

    private:
        
        static bool loadFontFile(const char* filename);
        static bool createPlanes(unsigned int startChar, unsigned int endChar, int panelWidth, int targetPixelHeight, const char* outSpacingGlyphsFilename);
        
        static void getGlyphAscentAndHeight(unsigned char* bmp, int width, int height, int& asc, int& desc);
        static unsigned char getPixel(unsigned char* bmp, int x, int y, int width, int height);
        static void calculateSizeAndPosition(unsigned int startGlyph, unsigned int endGlyph, int pixelHeight, unsigned char** bitmap, int* width, int* height, int* xoff, int* yoff, int& maxDeltaHeight);
        static unsigned char* getSubImage(unsigned char* bmp, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight);
        static void clearColorToZero(unsigned char* bmp, int width, int height);        
        static bool drawSubImage(unsigned char* bmp, unsigned char* subImage, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight);
        static unsigned char* cutGlyphRemoveSides(unsigned char* bmp, int width, int height);
};

#endif