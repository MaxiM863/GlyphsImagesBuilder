#ifndef GIB_HPP
#define GIB_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_truetype.h"

class GIB{

    public:

        static bool build(const char* fontFilename){
    
            GIB::loadFontFile(fontFilename);
            GIB::createPlanes(0, 256, 512, 32, "spacingGlyphs.dat");

            return true;
        };

    public:

        static inline std::vector<unsigned char> fontBuffer;
        static inline stbtt_fontinfo font;

        static inline unsigned char* ImageData;     

    private:
        
        static bool loadFontFile(const char* filename){
            try {

                const char* fontPath = "Fonts/arial.ttf"; // Replace with your font file

                // Open file in binary mode
                std::ifstream fontFile(fontPath, std::ios::binary | std::ios::ate);
                if (!fontFile) {
                    std::cerr << "Error: Could not open font file: " << fontPath << "\n";
                    return false;
                }

                // Get file size and read into buffer
                std::streamsize size = fontFile.tellg();
                fontFile.seekg(0, std::ios::beg);

                if (size <= 0) {
                    std::cerr << "Error: Font file is empty or unreadable.\n";
                    return false;
                }
                
                fontBuffer = std::vector<unsigned char>(static_cast<unsigned int>(size));
                
                if (!fontFile.read(reinterpret_cast<char*>(fontBuffer.data()), size)) {
                    std::cerr << "Error: Failed to read font file.\n";
                    return false;
                }

                // Initialize font
                
                int offset = stbtt_GetFontOffsetForIndex(fontBuffer.data(), 0); // 0 = first font in file
                if (offset < 0) {
                    std::cerr << "Error: Could not find font offset.\n";
                    return false;
                }

                if (!stbtt_InitFont(&font, fontBuffer.data(), offset)) {
                    std::cerr << "Error: stbtt_InitFont failed. Font may be corrupted or unsupported.\n";
                    return false;
                }

            } catch (const std::exception &e) {

                std::cerr << "Error: " << e.what() << "\n";
                
                return false;
            }

            return true;
        };

    static bool createPlanes(unsigned int startChar, unsigned int endChar, int panelWidth, int targetPixelHeight, const char* outSpacingGlyphsFilename){

        unsigned char** bitmap = nullptr;

        int* width = nullptr;
        int* height = nullptr;
        int* xoff = nullptr;
        int* yoff = nullptr;

        int maxHeight = 0;

        calculateSizeAndPosition(startChar, endChar, targetPixelHeight, bitmap, width, height, xoff, yoff, maxHeight);

        unsigned char* bitmapPlane = new unsigned char[panelWidth * panelWidth];

        clearColorToZero(bitmapPlane, panelWidth, panelWidth);

        int cntrH = 0;
        int cntrV = 0;
                
        unsigned int cc = startChar;

        unsigned char* dataSpacingGlypghs = new unsigned char[panelWidth * panelWidth * (sizeof(short) + sizeof(unsigned int))]; // store position and unicode value

        while(cc <  endChar)
        {

            drawSubImage(bitmapPlane, bitmap[cc - startChar], panelWidth, panelWidth, cntrH, cntrV, width[cc - startChar], height[cc - startChar]);

            cntrH += width[cc - startChar];

            if (cntrH > panelWidth)
            {
                cntrH = 0;
                cntrV += maxHeight;
            }
            else
            {
                cc++;

                //byte[] vv = BitConverter.GetBytes(cntrH);
                //fff.Write(vv, 0, 2);
            }
        }

        stbi_write_bmp("output.bmp", panelWidth, panelWidth, 1, bitmapPlane);

        //fff.Close();

        /*
        // Open file in binary mode
        std::ofstream fontFile(outSpacingGlyphsFilename, std::ios::binary);
        if (!fontFile) {
            std::cerr << "Error: Could not open font file: " << outSpacingGlyphsFilename << "\n";
            return false;
        }

        if (!fontFile.write(reinterpret_cast<char*>(fontBuffer.data()), size)) {
            std::cerr << "Error: Failed to write font file.\n";
            return false;
        }

        fontFile.close();*/

        return true;
    }

    static void GIB::clearColorToZero(unsigned char* bmp, int width, int height)
    {
        int length = width * height;

        for(int i = 0; i < length; i++)
        {
            bmp[i] = 0;
        }
    }

    static void GIB::calculateSizeAndPosition(unsigned int startGlyph, unsigned int endGlyph, int pixelHeight, unsigned char** bitmap, int* width, int* height, int* xoff, int* yoff, int& maxDeltaHeight)
    {
        //int ascent, descent, lineGap;

        //stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);


        //unsigned char* bbb = new unsigned char[4];
        
        // Scale factor to convert font units to pixels
        //float scale = stbtt_ScaleForPixelHeight(&font, pixelHeight);

        // Convert ascent to pixels
        //float ascentPx = ascent * scale;
        
        int lengthData = endGlyph - startGlyph;

        bitmap = new unsigned char*[lengthData];
        
        width = new int[lengthData];
        height = new int[lengthData];
        xoff = new int[lengthData];
        yoff = new int[lengthData];
        
        int maxHeight = 0;

        for (unsigned int i = startGlyph; i < endGlyph; i++)
        {
            //clearColorToZero(bitmap, 3 * height, 2 * height);

            int pos = i - startGlyph;
            // Get bitmap for the glyph
            float scale = stbtt_ScaleForPixelHeight(&font, (float)pixelHeight); // 32px height
            
            bitmap[pos] = stbtt_GetGlyphBitmap(&font, 0, scale, i, &width[pos], &height[pos], &xoff[pos], &yoff[pos]);

            if(maxHeight > height[pos]) maxHeight = height[pos];
        }

        maxDeltaHeight = maxHeight;
    };
        
    static void getGlyphAscentAndHeight(unsigned char* bmp, int width, int height, int& asc, int& desc){
    
        int fasc = 0;
        bool jump = false;

        unsigned char pixelColor;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                pixelColor = GIB::getPixel(bmp, x, y, width, height);
                
                if (pixelColor > 0) // Assuming black text on white background
                {
                    fasc = y;
                    jump = true;
                    break;
                }
            }

            if (jump) break;
        }

        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                pixelColor = GIB::getPixel(bmp, x, y, width, height);
                
                if (pixelColor > 0) // Assuming black text on white background
                {
                    asc = fasc;
                    desc = y;

                    return;
                }
            }
        }

        asc = height;
        desc = 0;
    };
        
    static unsigned char getPixel(unsigned char* bmp, int x, int y, int width, int height){

        unsigned char data;

        data = bmp[y * width + x];
        
        return data;
    };
        
   
    
    static unsigned char* getSubImage(unsigned char* bmp, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight){

        unsigned char* subImage = new unsigned char[destWidth * destHeight];

        int posSubX = 0;
        int posSubY = 0;
        int lineY = 0;

        for(int i = destPosX; i < destWidth; i++)
        {

            posSubX = i - destWidth;
            lineY = i * width;

            for(int j = destPosY; j < destHeight; j++)
            {

                subImage[posSubX * destWidth + j - destHeight] = bmp[lineY + j];
            }
        }

        return subImage;
    };
          
    static bool drawSubImage(unsigned char* bmp, unsigned char* subImage, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight){
    
        int posSubX = 0;
        int lineY = 0;

        for(int i = destPosX; i < destWidth; i++)
        {

            posSubX = i - destWidth;
            lineY = i * width;

            for(int j = destPosY; j < destHeight; j++)
            {

                bmp[posSubX * destWidth + j - destHeight] = subImage[lineY + j];
            }
        }

        return true;
    };
        
    static unsigned char* cutGlyphRemoveSides(unsigned char* bmp, int width, int height){
    
        int left = width;
        int right = 0;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                unsigned char bmpPixel = getPixel(bmp, x, y, width, height);

                if (bmpPixel > 0) // Assuming black text on white background
                {
                    if (x < left) left = x;
                    if (x > right) right = x;
                }
            }
        }

        if (right >= left)
        {

            return getSubImage(bmp, width, height, left, 0, right - left, height);
        }
        else
        {

            return nullptr; // Return a single pixel bitmap if no glyph is found
        }
    };
};

#endif